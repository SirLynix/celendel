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

bool XMLObject::save(QString filename)
{

    QString write_doc = dom.toString();

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        file.close();
        qDebug() << tr("Impossible writing file ") << filename;
        return false;
    }
    QTextStream stream(&file);
    stream << write_doc;
    file.close();
    qDebug() << tr("File successfully written");
    qDebug() << dom.toString();
    return true;
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
