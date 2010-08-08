#ifndef XMLOBJECT_H
#define XMLOBJECT_H
#include <QString>
#include <QObject>
#include <QMultiMap>
#include <QtXml/QtXml>

enum TRIGGER_TYPE {NOT_A_TRIGGER, ON_CREATION, ON_DESTRUCTION, ON_THROWN, ON_EQUIPPED};
enum ACTION_TYPE {NOT_AN_ACTION, ALERT_GM, ALERT_ALL_PLAYERS, ALERT_OWNER};

struct Event
{
    bool isValid() const { return action!=NOT_AN_ACTION; }
    QString name;
    ACTION_TYPE action;
    QString text;
};

class XMLObject : public QObject
{
Q_OBJECT
public:
    XMLObject();
    QString getName() const { return m_name; }

    //QByteArray serialiseXMLDocument();

   QString findAttribute(const QString& attribute);
   bool addAttributeOnTag(const QString& tagName, const QString& attribute, const QString& value);
   void addAttributeWithTag(const QString& NewTagName, const QString& attribute, const QString& value);

   bool save(const QString& filename);
   bool load(const QString& filename);


private:
    bool onEvent(TRIGGER_TYPE);
    bool doAction(ACTION_TYPE act, const QString& txt);

signals:
    void alertGM(QString message);
    void alertPlayer(QString message, bool toAll);

protected:

    void loadEvents();

    QString m_name;
    QString m_infos;
    QDomDocument m_dom;
    bool m_isSynced;

    QMultiMap<TRIGGER_TYPE, Event> m_eventMap;
};

#endif // XMLOBJECT_H
