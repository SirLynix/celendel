#include "xmlobject.h"
#include <QtXml>
#include <QString>

int alea(int min,int max){static bool first=true;if(first){srand(time(NULL));first=false;alea(0,150);}return (int)(min+((float)rand()/RAND_MAX*(max-min+1)));}

XMLObject::XMLObject()
{
    m_typePrefix = "XMLObject";
    m_name = "Default XML Object";

    m_isSynced=true;
    m_life=0;
    m_destroyable=false;
    m_error=false;
}

XMLObject::~XMLObject()
{
    QMultiMap<TRIGGER_TYPE, Event>::const_iterator i=m_eventMap.constBegin();while(i!=m_eventMap.constEnd())
    {
        if(i.value().action==ALERT_SPECIAL_PLAYER)
            delete i.value().data.plyPatern; //Must be NULL or allocated, else behavior is undefined.
        if(i.value().action==USE_OBJECT)
            delete i.value().data.objPatern;
        if(i.value().action==DAMAGE)
            delete i.value().data.amount;

        ++i;
    }
}

void XMLObject::damage(uint dmg)
{
    if(m_destroyable)
    {
        if(dmg>=m_life)
        {
            m_life=0;
            emit destroyed(dmg);
        }
        else
            m_life-=dmg;

        emit damaged(dmg);
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
    return qCompress(synchronise().toUtf8());
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

        if(i.value().action==ALERT_SPECIAL_PLAYER&&i.value().data.ptr!=NULL)
        {
           if(!i.value().data.plyPatern->nameRegExp.isEmpty())
            s+="player_name_regexp=\""+i.value().data.plyPatern->nameRegExp+"\" ";

           if(!i.value().data.plyPatern->classRegExp.isEmpty())
            s+="player_class_regexp=\""+i.value().data.plyPatern->classRegExp+"\" ";
        }
        else if(i.value().action==USE_OBJECT&&i.value().data.ptr!=NULL)
        {
            if(!i.value().data.objPatern->nameRegExp.isEmpty())
             s+="target_object_name_regexp=\""+i.value().data.objPatern->nameRegExp+"\" ";
        }
        else if(i.value().action==DAMAGE&&i.value().data.ptr!=NULL)
        {
            s+="amount=\""+QString::number(i.value().data.amount->a)+";"+QString::number(i.value().data.amount->b)+";"+QString::number(i.value().data.amount->c);
            int size=i.value().data.amount->array.size();
            for(int k=0;k<size;++k)
                s+=";"+QString::number(i.value().data.amount->array[k]);
            s+="\" ";
        }

        s+="/>\n";
        ++i;
    }

    synchroniseCustomData(s);

    s+="</"+m_typePrefix+">\n";

    m_dom.setContent(s);
    m_isSynced=false;

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

    if(e.randomFactor>0)
    {
        if(alea(0,e.randomFactor))
            return false;
    }

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
    else if(e.action==DAMAGE)
    {
        if(e.data.ptr==NULL)
        {
            qDebug() << "Error : invalid damage event.";
            return false;
        }

        damage(e.data.amount->a);
        return true;
    }
    else if(e.action==USE_OBJECT)
    {
        if(e.data.ptr==NULL)
        {
            this->use(true);
        }
        else
        {
            emit useObject(*e.data.objPatern);
        }
    }

    return false;
}

bool XMLObject::use(bool isScript)
{
    emit used(isScript);
    return onEvent(ON_USE);
}

bool XMLObject::onEvent(TRIGGER_TYPE trig)
{
    if(trig==NOT_A_TRIGGER)
        return false;

    QList<Event> list=m_eventMap.values(trig);
    bool ret=false;

    for(int i=0;i<list.size();++i)
    {
        ret=doAction(list[i])?true:ret;
    }

    return ret;
}

#define CAR(x) if(t==#x) return x;
#define CI CAR(ON_CREATION)CAR(ON_DESTRUCTION)CAR(ON_THROWN)CAR(ON_EQUIPPED)CAR(ON_OWNER_CHANGE)CAR(ON_USE)CAR(REGULAR)
TRIGGER_TYPE stringToTrigger(const QString& s){QString t=s.toUpper();CI return NOT_A_TRIGGER;}
#define CM CAR(ALERT_GM)CAR(ALERT_ALL_PLAYERS)CAR(ALERT_OWNER)CAR(ALERT_SPECIAL_PLAYER)CAR(FEED)CAR(DAMAGE)CAR(DESTROY)CAR(USE_OBJECT)
ACTION_TYPE stringToAction(const QString& s){QString t=s.toUpper();CM return NOT_AN_ACTION;}
#undef CAR
#define CAR(x) if(s==x) return #x;
QString triggerToString(TRIGGER_TYPE s){CI return QString();}
QString actionToString(ACTION_TYPE s){CM return QString();}
#undef CAR
#undef CI
#undef CM

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
                    else if(i.key()=="RANDOM")
                    {
                        ev.randomFactor=i.value().toUInt();
                    }
                    else if(i.key()=="TEXT")
                    {
                        ev.text=i.value();
                    }
                    else if(i.key()=="AMOUNT")
                    {
                        if(ev.action==DAMAGE)
                        {
                            if(ev.data.ptr==NULL)
                            {
                                ev.data.amount=new Amount;
                            }
                            QStringList spl=i.value().split(';', QString::SkipEmptyParts);
                            if(spl.size()==0)
                                qDebug() << "Error : empty argument";
                            else
                            {
                                if(spl.size()>=1)
                                    ev.data.amount->a=spl[0].toInt();
                                if(spl.size()>=2)
                                    ev.data.amount->b=spl[1].toInt();
                                if(spl.size()>=3)
                                    ev.data.amount->c=spl[2].toInt();
                                if(spl.size()>=4)
                                    for(int i=3; i<spl.size(); ++i)
                                        ev.data.amount->array.append(spl[i].toInt());
                            }
                        }
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
                    else if(i.key()=="TARGET_OBJECT_NAME_REGEXP")
                    {
                        if(ev.action==USE_OBJECT)
                        {
                            if(ev.data.ptr==NULL)
                                ev.data.objPatern=new ObjectPatern;
                            ev.data.objPatern->nameRegExp=i.value();
                        }
                        else
                            qDebug() << "Error : attribute " << i.key() << " does not match with action type.";
                    }

                    ++i;
                }

                if(ev.isValid())
                {
                    if(tt==ON_USE&&ev.action==USE_OBJECT&&ev.data.ptr==NULL)
                    {
                        qDebug() << "Error : circular event detected : skipping...";
                    }
                    else if(ev.action==ALERT_SPECIAL_PLAYER&&ev.data.ptr==NULL)
                    {
                        qDebug() << "Error : special player undefined. Skipping...";
                    }
                    else
                        m_eventMap.insert(tt,ev);
                }
            }
        }
        n = n.nextSibling();
    }
}

#define ER(x) {qDebug() << x; m_error=true; return true;}

bool XMLObject::loadFromMemory(const QByteArray& data, bool forceLoading)
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
        m_isSynced=true;
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
