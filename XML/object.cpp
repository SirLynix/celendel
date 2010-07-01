#include "object.h"


Object::Object(QString filename, QString name, int weight, QString infos)
{
    if(filename != "")
    {
        XMLObject::load(filename);
    }
    else
    {
        m_name = name;
        m_infos = infos;
        m_weight = weight;
        m_owner = NULL;
        baseDoc();
    }
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

void Object::baseDoc()
{
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
}


