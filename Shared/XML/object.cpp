#include "object.h"
#include <QRegExp>
#include "person.h"

Object::Object(const QString& filename)
{
    m_class = SIMPLE_OBJECT;
    m_typePrefix = "Object";
    m_name = "Default Object";
    m_infos = "A default constructed object";
    m_owner = NULL;
    MaterialThing::load(filename);
}

Object::Object(int mass, const QString& name, const QString& infos)
{
    m_class = SIMPLE_OBJECT;
    m_typePrefix = "Object";
    m_name = name;
    m_infos = infos;
    m_mass = mass;
    m_owner = NULL;
}

Object::~Object()
{
    if(m_owner!=NULL)
        m_owner->removeObject(this);
}

#define C(x) if(c==x) return #x; //I'm not sure I can do shorter...
#define CA C(OH_WEAPON) C(TH_WEAPON) C(SHOULDER_PIECE) C(HELMET) C(TORSO_PIECE) C(GLOVES) C(ARMS_PIECE) C(LEGS_PIECE) C(BOOTS) C(UNDERWEAR) C(CONSUMMABLE) C(RINGS) C(AMULET) C(ARTIFACTS)
QString objectClassToString(OBJECT_CLASS c){CA return "OTHER";}
#undef C
#define C(x) if(c==#x) return x;
OBJECT_CLASS stringToObjectClass(QString c){c=c.toUpper(); CA return OTHER;}
#undef C
#undef CA

bool Object::loadCustomData()
{
    QDomElement docElem = m_dom.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        QString tn=e.tagName().toUpper();
        if(tn=="CHARACTERISTICS")
        {
            QMultiMap<QString,QString> atrmap=extractElementAttributes(e);

            {QString n; if(!(n=atrmap.value("OBJECT_CLASS")).isEmpty()) { m_class=stringToObjectClass(n); if(m_class==OTHER) {m_customType=n;} } }
        }

        n = n.nextSibling();
    }
    return false;
}


bool Object::matchPatern(const ObjectPatern& patern)
{
    if(!patern.nameRegExp.isEmpty())
    {
        if(!QRegExp(patern.nameRegExp).exactMatch(m_name))
            return false;
    }
    if(m_owner!=NULL)
        return m_owner->matchPatern(patern.owner);

    return true;
}

void Object::synchroniseCustomData(QString& s)
{
    MaterialThing::synchroniseCustomData(s);

    s+="<Characteristics  ";

    if(m_class==OTHER)
        s+="object_class=\""+m_customType+"\" ";
    else
        s+="object_class=\""+objectClassToString(m_class)+"\" ";

    s+="/>\n";
}

void Object::changeOwner(Person *owner)
{
    onEvent(ON_OWNER_CHANGE);
    m_owner=owner;
}

void Object::throwUp()
{
    onEvent(ON_DESTRUCTION);
}

