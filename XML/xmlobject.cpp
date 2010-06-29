#include "xmlobject.h"
#include <QtXml/QtXml>
#include <QString>

XMLObject::XMLObject()
{

    m_name = "Objet XML";
    m_infos = "Créé par XMLObjet";


}

XMLObject::~XMLObject()
{
}



bool XMLObject::load(QString filename)
{

   return false;
}

/*void XMLObject::alertMJ(QString message) const
{

}

void XMLObject::alertPlayer(QString message, bool toAll) const
{

}*/

QString XMLObject::getName()
{
    return m_name;
}
