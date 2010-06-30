#include "object.h"

Object::Object()
{
    m_weight = 1;
    m_owner = NULL;
    m_name = "Objet";
    m_infos = "Cet Objet est un Objet par defaut";

}

Object::Object(QString name, int weight, QString infos)
{
        m_name = name;
        m_infos = infos;
        m_weight = weight;
        m_owner = NULL;
}

bool Object::throwUp()
{
    m_owner = NULL;
    return false;
}

bool Object::give(Person *target)
{
    m_owner = target;
    return false;
}

void Object::save(QTextStream &fileTxtStr)
{
    dom.clear();
    QDomElement docElem = dom.createElement("XMLObject");
    dom.appendChild(docElem);

    QDomElement general_elem = dom.createElement("General");
    general_elem.setAttribute("Name", m_name);
    general_elem.setAttribute("Description", m_infos);
    docElem.appendChild(general_elem);

    QDomElement object_elem = dom.createElement("Object");
    object_elem.setAttribute("Weight", m_weight);
    if(m_owner != NULL)
    {
        object_elem.setAttribute("Owner", m_owner->getName());
    }
    else { object_elem.setAttribute("Owner", "None"); }
    docElem.appendChild(object_elem);

    fileTxtStr << dom.toString();
}

bool Object::save(QString filename)
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


