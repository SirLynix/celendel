#include "person.h"
#define VIE_MAX 10

Person::Person()
{
    m_vie = VIE_MAX;
    m_behavior = BH_UNKNOWN;
    m_name = "Personnage";
    m_infos = "Ce personnage est cree par defaut";
}

Person::Person(QString name, BEHAVIOR_TYPE bh, QString infos)
{
        m_name = name;
        m_vie = VIE_MAX;
        m_behavior = bh;
        m_infos = infos;

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

void Person::save(QTextStream &fileTxtStr)
{
    dom.clear();
    QDomElement docElem = dom.createElement("XMLObject");
    dom.appendChild(docElem);

    QDomElement general_elem = dom.createElement("General");
    general_elem.setAttribute("Name", m_name);
    general_elem.setAttribute("Description", m_infos);
    docElem.appendChild(general_elem);

    QDomElement perso_elem = dom.createElement("Person");
    perso_elem.setAttribute("Life", m_vie);
    perso_elem.setAttribute("Behavior", m_behavior);
    docElem.appendChild(perso_elem);

    fileTxtStr << dom.toString();
}

bool Person::save(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        file.close();
        qDebug() << tr("Impossible writing file ") << filename;
        return false;
    }
    QTextStream stream(&file);
    save(stream);
    file.close();
    qDebug() << tr("File successfuly written ");
    return true;
}


