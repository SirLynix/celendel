#include "person.h"
#define VIE_MAX 10


Person::Person(QString filename,QString name, BEHAVIOR_TYPE bh, QString infos)
{
        if(filename != "")
        {
            XMLObject::load(filename);
        }
        else
        {
            m_name = name;
            m_vie = VIE_MAX;
            m_behavior = bh;
            m_infos = infos;
            baseDoc();
        }
}

bool Person::damage(unsigned int damage)
{
    m_vie -= damage;
    if(m_vie <= 0)
    {
        m_vie = 0;
        return true;
    }
    return false;
}

bool Person::heal(unsigned int amount)
{
    m_vie += amount;
    if(m_vie >= VIE_MAX)
    {
        m_vie = VIE_MAX;
        return true;
    }
    return false;
}

void Person::baseDoc()
{
    QDomElement docElem = m_dom.createElement("XMLObject");
    m_dom.appendChild(docElem);

    QDomElement general_elem = m_dom.createElement("General");
    general_elem.setAttribute("Name", m_name);
    general_elem.setAttribute("Description", m_infos);
    docElem.appendChild(general_elem);

    QDomElement perso_elem = m_dom.createElement("Person");
    perso_elem.setAttribute("Life", m_vie);
    perso_elem.setAttribute("Behavior", m_behavior);
    docElem.appendChild(perso_elem);
}

