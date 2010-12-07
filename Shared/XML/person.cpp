#include "person.h"
#include <QRegExp>
#include "Object.h"


#define C(x) if(c==x) return #x; //I'm not sure I can do shorter...
#define CA C(BH_PLAYER) C(BH_ENNEMY) C(BH_AGGRESSIVE) C(BH_UNKNOWN)
QString BehaviorTypeToString(BEHAVIOR_TYPE c){CA return "BH_UNKNOWN";}
#undef C
#define C(x) if(c==#x) return x;
BEHAVIOR_TYPE StringToBehaviorType(QString c){c=c.toUpper(); CA return BH_UNKNOWN;}
#undef C
#undef CA

Person::Person(const QString& filename, const QString& name, BEHAVIOR_TYPE bh, const QString& infos)
{
    m_typePrefix = "Person";
    if(filename != "")
    {
        MaterialThing::load(filename);
    }
    else
    {
        m_name=name;
        m_behavior=bh;
        m_infos=infos;
    }
}

bool Person::loadCustomData()
{
    QDomElement docElem = m_dom.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        QString tn=e.tagName().toUpper();
        if(tn=="BEHAVIOR")
        {
            QMultiMap<QString,QString> atrmap=extractElementAttributes(e);
            QString n;
            if(!(n=atrmap.value("TYPE")).isEmpty())
            {
                m_behavior=StringToBehaviorType(n);
            }

        }
        else if(tn=="LANGUAGES")
        {
            QMultiMap<QString,QString> atrmap=extractElementAttributes(e);
            QString n;
            if(!(n=atrmap.value("NAME")).isEmpty())
            {
                int prct=100;
                QString sprct; if(!(sprct=atrmap.value("ABILITY")).isEmpty()) {prct=sprct.toInt(); if(prct>100) {prct=100;} if(prct<0) {prct=0;} }
                m_languages[n]=prct;
            }

        }

        n = n.nextSibling();
    }

    return false;
}


void Person::synchroniseCustomData(QString& s)
{
    MaterialThing::synchroniseCustomData(s);
    s+="<Behavior type=\""+BehaviorTypeToString(m_behavior)+"\" ";
    s+="/>\n";
    s+="<Characteristics class=\""+m_class+"\" ";
    s+="/>\n";

    QMap<QString, int>::const_iterator i = m_languages.constBegin();
    while (i!=m_languages.constEnd())
    {
        s+="<Languages name=\""+i.key()+"\" ability="+i.value()+"/>\n";
        ++i;
    }
}


bool Person::matchPatern(const PlayerPatern& patern)
{
    if(patern.human==true&&m_behavior!=BH_PLAYER)
        return false;

    if(!patern.nameRegExp.isEmpty())
    {
        if(!QRegExp(patern.nameRegExp).exactMatch(m_name))
            return false;
    }
    if(!patern.classRegExp.isEmpty())
    {
        if(!QRegExp(patern.classRegExp).exactMatch(m_class))
            return false;
    }

    return true;
}


ObjectPtr Person::addObject(const QString& filename)
{
    return addObject(ObjectPtr(new Object(filename)));
}

ObjectPtr Person::addObject(Object* p)
{
    return addObject(ObjectPtr(p));
}

ObjectPtr Person::addObject(const ObjectPtr& o)
{
    if(m_inventory.contains(o))
        return ObjectPtr();

    m_inventory.append(o);

    if(o->m_owner != NULL)
        o->m_owner->removeObject(o);

    o->changeOwner(this);
    connect(o.get(), SIGNAL(destroyed()), this, SLOT(objectDestroyed()));
    return o;
}

void Person::removeObject(const Object*const o)
{
    for(int i=0;i<m_inventory.size();++i)
    {
        if(m_inventory[i].get()==o)
            removeObject(m_inventory[i]);
    }
}

ObjectPtr Person::removeObject(const ObjectPtr& o)
{
    if(!m_inventory.contains(o))
        return ObjectPtr();

    m_inventory.removeAll(o);
    o->changeOwner(NULL);
    disconnect(o.get(), SIGNAL(destroyed()), this, SLOT(objectDestroyed()));
    return o;
}

ObjectPtr Person::getObjectSmartPtr(const Object* o) const
{
    for(int i=0, m=m_inventory.size();i<m;++i)
    {
        if(m_inventory[i].get()==o)
            return m_inventory[i];
    }

    return ObjectPtr();
}

void Person::objectDestroyed()
{
    Object *obj_p = qobject_cast<Object*>(sender());
    if (obj_p==NULL) //Wait, what ?
        return;
    ObjectPtr obj=getObjectSmartPtr(obj_p);
    if(obj.get()==NULL) //Object is not in inventory - seriously, WTF !?!
        return;

    removeObject(obj);
}

/* Connecter destruction objet � slot perso */

