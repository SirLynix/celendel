#ifndef XMLOBJECT_H
#define XMLOBJECT_H
#include <QString>
#include <QObject>
#include <QtXml/QtXml>

//enum TRIGGER_TYPE { };

class XMLObject : public QObject
{
Q_OBJECT
public:
    XMLObject();
    ~XMLObject();
    QString getName();
    //QByteArray serialiseXMLDocument();

   QString findAttribute(QString attribute);
   bool addAttributeOnTag(QString tagName, QString attribute, QString value);
   void addAttributeWithTag(QString NewTagName, QString attribute, QString value);

   bool save(QString filename);
   bool load(QString filename);


private slots:
    //void onEvent();

/*signals:
    void alertMJ(QString message) const;
    void alertPlayer(QString message, bool toAll=true) const;*/

protected:
    QString m_name;
    QString m_infos;
    QDomDocument dom;
    bool isSynced;

    //QMap<TRIGGER_TYPE, Event> m_eventMap;
};

#endif // XMLOBJECT_H
