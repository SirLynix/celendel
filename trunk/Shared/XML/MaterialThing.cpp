#include "MaterialThing.h"

#include "..\Constants.h"

MaterialThing::MaterialThing(const QString& filename)
{
    m_typePrefix = "MaterialThing";
    m_mass = 1;
    m_life=0;
    m_destroyable=false;

    if(!filename.isEmpty())
        XMLObject::load(filename);
}

void MaterialThing::synchroniseCustomData(QString& s)
{
    s+="<Characteristics weight=\""+QString::number(m_mass)+"\" ";
    if(!m_name.isEmpty())
        s+="name=\""+m_name+"\" ";
    s+="/>\n";
}

#define IE(x) {QString n; if(!(n=atrmap.value(QString(#x).toUpper())).isEmpty()) {m_##x=n;}}
#define IEI(x) {QString n; if(!(n=atrmap.value(QString(#x).toUpper())).isEmpty()) {m_##x=n.toUInt();}}

bool MaterialThing::loadCustomData()
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
            IEI(mass);
            IE(name);
        }

        n = n.nextSibling();
    }
    return false;
}
#undef IE
#undef IEI


bool MaterialThing::doAction(const Event& e, bool randomFactor)
{
    if(e.randomFactor>0&&randomFactor)
    {
        if(alea(0,e.randomFactor))
            return false;
    }

    if(e.action==DAMAGE)
    {
        if(e.data.ptr==NULL)
        {
            qDebug() << "Error : invalid damage event.";
            return false;
        }

        damage(e.data.amount->a);
        return true;
    }


    return XMLObject::doAction(e, false);
}

void MaterialThing::damage(uint dmg)
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
