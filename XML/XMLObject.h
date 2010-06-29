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
    bool save(QString filename);
    bool save(QTextStream& fileTxtStr);
    bool load(QString filename);
    QString getName();


private slots:
    //void onEvent();

/*signals:
    void alertMJ(QString message) const;
    void alertPlayer(QString message, bool toAll=true) const;*/

protected:
    QString m_name;
    QString m_infos;
    QDomDocument dom;

    //QMap<TRIGGER_TYPE, Event> m_eventMap;
};

#endif // XMLOBJECT_H
