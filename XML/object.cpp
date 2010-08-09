#include "object.h"

Object::Object(const QString& filename)
{
    m_typePrefix = "Object";
    XMLObject::load(filename);
}

Object::Object(int weight, const QString& name, const QString& infos)
{
    m_name = name;
    m_infos = infos;
    m_weight = weight;
    m_owner = NULL;
   // baseDoc();
}

bool Object::onEvent(TRIGGER_TYPE tt)
{
    return XMLObject::onEvent(tt);
}

#define IE(x) {QString n; if(!(n=atrmap.value(QString(#x).toUpper())).isEmpty()) {m_##x=n;}}
#define IEI(x) {QString n; if(!(n=atrmap.value(QString(#x).toUpper())).isEmpty()) {m_##x=n.toUInt();}}
bool Object::loadCustomData()
{
    QDomElement docElem = m_dom.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement();

        if(e.tagName()=="Characteristics")
        {
            QMultiMap<QString,QString> atrmap=extractElementAttributes(e);
            IEI(weight);
            IE(name);
        }

        n = n.nextSibling();
    }
    return false;
}
#undef IE
#undef IEI

void Object::synchroniseCustomData(QString& s)
{
    s+="<Characteristics weight=\""+QString::number(m_weight)+"\" ";
    if(!m_name.isEmpty())
        s+="name=\""+m_name+"\" ";
    s+=">\n";
}

bool Object::throwUp()
{
    m_owner = NULL;
    onEvent(ON_DESTRUCTION);
    return false;
}

bool Object::give(Person *target)
{
    m_owner = target;
    onEvent(ON_OWNER_CHANGE);
    return false;
}
