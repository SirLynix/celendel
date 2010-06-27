#include "object.h"

Object::Object()
{
    m_weight = 1;
    m_name = "Objet";
    m_infos = "Cet Objet est un Objet par defaut";
    QDomElement docElem = dom.createElement("XMLObject");
    dom.appendChild(docElem);

    QDomElement general_elem = dom.createElement("General");
    general_elem.setAttribute("Name", m_name);
    general_elem.setAttribute("Description", m_infos);
    docElem.appendChild(general_elem);

    QDomElement object_elem = dom.createElement("Object");
    object_elem.setAttribute("Weight", m_weight);
    docElem.appendChild(object_elem);

}

bool Object::throwUp()
{
    return false;
}

bool Object::give()
{
    return false;
}
