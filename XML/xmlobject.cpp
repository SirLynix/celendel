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

/*QByteArray XMLObject::serialiseXMLDocument()
{



}*/

QString XMLObject::findAttribute(QString attribute)
{
    QDomElement docElem = dom.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        if(e.attribute(attribute,"") != "")
        {
            return e.attribute(attribute);
        }
        n = n.nextSibling();
    }
    return "";
}

bool XMLObject::addAttributeOnTag(QString tagName, QString attribute, QString value)
{
    QDomElement docElem = dom.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        if(e.tagName() == tagName)
        {
            e.setAttribute(attribute, value);

            n.replaceChild(e,n.toElement());
            isSynced = false;
            return true;
        }
        n = n.nextSibling();
    }
    return false;
}
void XMLObject::addAttributeWithTag(QString NewTagName, QString attribute, QString value)
{
    QDomElement docElem = dom.documentElement();

    QDomElement newElement = dom.createElement(NewTagName);
    newElement.setAttribute(attribute,value);
    docElem.appendChild(newElement);

    isSynced = false;
}

bool XMLObject::save(QString filename)
{

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        file.close();
        qDebug() << tr("Impossible writing file ") << filename;
        return false;
    }

    QTextStream stream(&file);

    stream << dom.toString();

    file.close();
    qDebug() << tr("File successfuly written ");
    return true;
    isSynced = true;
}

bool XMLObject::load(QString filename)
{
    if(!isSynced)
    {
        qDebug() << tr("RAM document is modified, please save before");
        return false;
    }

    dom.clear();
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        file.close();
        qDebug() << tr("Impossible opening file ") << filename;
        return false;
    }
    if(!dom.setContent(&file))
    {
        qDebug() << tr("error occured during XML association in RAM");
        return false;
    }
    return true;
}
