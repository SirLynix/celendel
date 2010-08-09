#include "xmlobject.h"
#include <QtXml>
#include <QString>

XMLObject::XMLObject()
{
    m_typePrefix = "XMLObject";
    m_name = "Objet XML";
    m_infos = "Créé par XMLObjet";

    m_error=false;
}

XMLObject::~XMLObject()
{
    QMultiMap<TRIGGER_TYPE, Event>::const_iterator i=m_eventMap.constBegin();while(i!=m_eventMap.constEnd())
    {
        if(i.value().action==ALERT_SPECIAL_PLAYER)
            delete i.value().data.plyPatern; //Must be NULL or allocated, else behavior is undefined.
        ++i;
    }
}

bool XMLObject::unserialiseXMLDocument(const QByteArray& b)
{
    QByteArray dta=qUncompress(b);
    if(dta.isEmpty())
    {
        qDebug() << tr("Error : invalid format");
        return true;
    }

    return loadFromMemory(dta, true);
}

QByteArray XMLObject::serialiseXMLDocument()
{
    return qCompress(synchronise().toLatin1());
}

QString XMLObject::synchronise()
{
    if(m_error)
        return QString();

    QString s;
    s.reserve(150);
    s='<'+m_typePrefix+">\n";
    QMultiMap<TRIGGER_TYPE, Event>::const_iterator i=m_eventMap.constBegin();while(i!=m_eventMap.constEnd())
    {
        s+=" <Event trigger=\""+triggerToString(i.key())+"\" action=\""+actionToString(i.value().action)+"\" text=\""+i.value().text+"\" ";
        if(!i.value().name.isEmpty())
            s+="name=\""+i.value().name+"\" ";

        if(i.value().action==ALERT_SPECIAL_PLAYER)
        {
           if(!i.value().data.plyPatern->nameRegExp.isEmpty())
            s+="player_name_regexp=\""+i.value().data.plyPatern->nameRegExp+"\" ";

           if(!i.value().data.plyPatern->classRegExp.isEmpty())
            s+="player_class_regexp=\""+i.value().data.plyPatern->classRegExp+"\" ";
        }

        s+=">\n";
        ++i;
    }

    synchroniseCustomData(s);

    s+="</"+m_typePrefix+">\n";
    m_dom.setContent(s);

    return s;
}

bool XMLObject::save(const QString& filename)
{
    if(error())
        return true;

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << tr("Impossible to write file ") << filename;
        return true;
    }

    file.write(synchronise().toLatin1());

    qDebug() << tr("File successfuly written.");
    m_isSynced = true;
    return false;
}

bool XMLObject::doAction(const Event& e)
{
    if(e.action==NOT_AN_ACTION)
        return false;

    if(e.action==ALERT_OWNER)
    {
        qDebug() << "ALERT OWNER : " << e.text;
        emit alertOwner(e.text);
        return true;
    }
    else if(e.action==ALERT_ALL_PLAYERS)
    {
        qDebug() << "ALERT ALL PLAYERS : " << e.text;
        emit alertAllPlayers(e.text);
        return true;
    }
    else if(e.action==ALERT_SPECIAL_PLAYER)
    {
        qDebug() << "ALERT SPECIAL PLAYER ("<<e.data.plyPatern->nameRegExp << ") : " << e.text;
        emit alertPlayers(e.text, *e.data.plyPatern);
        return true;
    }

    return false;
}

bool XMLObject::onEvent(TRIGGER_TYPE trig)
{
    if(trig==NOT_A_TRIGGER)
        return false;

    QList<Event> list=m_eventMap.values(trig);
    bool ret=false;

    for(int i=0;i<list.size();++i)
    {
        doAction(list[i]);
    }

    return ret;
}

#define CAR(x) if(t==#x) return x; //Check&return
TRIGGER_TYPE stringToTrigger(const QString& s)
{
    QString t=s.toUpper();

    CAR(ON_CREATION);
    CAR(ON_DESTRUCTION);
    CAR(ON_THROWN);
    CAR(ON_EQUIPPED);
    CAR(ON_OWNER_CHANGE);

    return NOT_A_TRIGGER;
}

ACTION_TYPE stringToAction(const QString& s)
{
    QString t=s.toUpper();

    CAR(ALERT_GM);
    CAR(ALERT_ALL_PLAYERS);
    CAR(ALERT_OWNER);
    CAR(ALERT_SPECIAL_PLAYER);

    return NOT_AN_ACTION;
}
#undef CAR
#define CAR(x) if(s==x) return #x; //Check&return
QString triggerToString(TRIGGER_TYPE s)
{
    CAR(ON_CREATION);
    CAR(ON_DESTRUCTION);
    CAR(ON_THROWN);
    CAR(ON_EQUIPPED);
    CAR(ON_OWNER_CHANGE);

    return QString();
}

QString actionToString(ACTION_TYPE s)
{
    CAR(ALERT_GM);
    CAR(ALERT_ALL_PLAYERS);
    CAR(ALERT_OWNER);
    CAR(ALERT_SPECIAL_PLAYER);

    return QString();
}

QMultiMap<QString,QString> extractElementAttributes(const QDomElement& e)
{
    QMultiMap<QString, QString> map;
    QDomNamedNodeMap d=e.attributes();
    for(int i=0;i<d.size();++i)
    {
        QDomAttr attr=d.item(i).toAttr();
        map.insert(attr.name().toUpper(), attr.value());
    }
    return map;
}

void XMLObject::loadEvents()
{
    m_eventMap.clear();

    QDomElement docElem = m_dom.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement();

        if(e.tagName()=="Event")
        {
            QMultiMap<QString,QString> atrmap=extractElementAttributes(e);
            TRIGGER_TYPE tt=NOT_A_TRIGGER;
            if((tt=stringToTrigger(atrmap.value("TRIGGER")))==NOT_A_TRIGGER)
            {
                qDebug() << "Error : invalid trigger";
            }
            else
            {
                Event ev;

                QMultiMap<QString, QString>::const_iterator i=atrmap.constBegin();while(i!=atrmap.constEnd())
                {
                    if(i.key()=="ACTION")
                    {
                        ACTION_TYPE at=stringToAction(i.value());
                        if(at!=NOT_AN_ACTION)
                        {
                            if(ev.data.ptr==NULL&&ev.action==NOT_AN_ACTION)
                            {
                                ev.action=at;
                            }
                            else
                                qDebug() << "Error : multiple 'action' attribute in a single event. Keeping the first one...";
                        }
                        else
                            qDebug() << "Error : unknow action.";
                    }
                    else if(i.key()=="NAME")
                    {
                        ev.name=i.value();
                    }
                    else if(i.key()=="TEXT")
                    {
                        ev.text=i.value();
                    }
                    else if(i.key()=="PLAYER_NAME_REGEXP")
                    {
                        if(ev.action==ALERT_SPECIAL_PLAYER)
                        {
                            if(ev.data.plyPatern==NULL)
                            {
                                ev.data.plyPatern=new PlayerPatern;
                            }
                            ev.data.plyPatern->nameRegExp=i.value();

                        }
                        else
                            qDebug() << "Error : attribute " << i.key() << " does not match with action type.";
                    }
                    else if(i.key()=="PLAYER_CLASS_REGEXP")
                    {
                        if(ev.action==ALERT_SPECIAL_PLAYER)
                        {
                            if(ev.data.ptr==NULL)
                                ev.data.plyPatern=new PlayerPatern;
                            ev.data.plyPatern->classRegExp=i.value();
                        }
                        else
                            qDebug() << "Error : attribute " << i.key() << " does not match with action type.";
                    }
                    ++i;
                }

                if(ev.isValid())
                    m_eventMap.insert(tt,ev);
            }
        }
        n = n.nextSibling();
    }
}

#define ER(x) {qDebug() << x; m_error=true; return true;}

bool XMLObject::loadFromMemory(const QString& data, bool forceLoading)
{
    if(!m_isSynced&&!forceLoading)
        ER(tr("RAM document is modified, please save before loading"));

    m_dom.clear();
    QString error;
    if(!m_dom.setContent(data, &error))
        ER(tr("An error occured during XML association in RAM : \"%1\"").arg(error));


    if(m_dom.documentElement().nodeName()!=m_typePrefix)
        ER(tr("Error : invalid format (\"%1\", requested \"%2\")").arg(m_dom.documentElement().nodeName(),m_typePrefix));

    loadEvents();

    if(!loadCustomData())
    {
        qDebug() << "Here :" << synchronise();
        onEvent(ON_CREATION);
        return false;
    }
    else
    {
        return true;
    }
}

bool XMLObject::load(const QString& filename, bool forceLoading)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        file.close();
        ER(tr("Cannot open file \"%1\"").arg(filename));
    }

    return loadFromMemory(file.readAll());
}
#undef ER
