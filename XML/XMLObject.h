#ifndef XMLOBJECT_H
#define XMLOBJECT_H
#include <QString>
#include <QObject>
#include <QMultiMap>
#include <QtXml/QtXml>

enum TRIGGER_TYPE {NOT_A_TRIGGER, ON_CREATION, ON_DESTRUCTION, ON_THROWN, ON_EQUIPPED, ON_OWNER_CHANGE};
enum ACTION_TYPE {NOT_AN_ACTION, ALERT_GM, ALERT_ALL_PLAYERS, ALERT_OWNER, ALERT_SPECIAL_PLAYER};

TRIGGER_TYPE stringToTrigger(const QString& s);
ACTION_TYPE stringToAction(const QString& s);

struct PlayerPatern
{
    PlayerPatern():human(false) {}
    QString nameRegExp;
    QString classRegExp;
    bool human;
};

struct Event
{
    Event(ACTION_TYPE act=NOT_AN_ACTION) : action(act) { data.plyPatern=NULL; }
    bool isValid() const { return action!=NOT_AN_ACTION; }
    QString name;
    ACTION_TYPE action;
    QString text;
    union {void* ptr; PlayerPatern* plyPatern; } data;
   // void* data;
};

class XMLObject : public QObject
{
Q_OBJECT
public:
    XMLObject();
    ~XMLObject();

    QString getName() const { return m_name; }

    //QByteArray serialiseXMLDocument();

   QString findAttribute(const QString& attribute);
   bool addAttributeOnTag(const QString& tagName, const QString& attribute, const QString& value);
   void addAttributeWithTag(const QString& NewTagName, const QString& attribute, const QString& value);

   bool save(const QString& filename);
   bool load(const QString& filename);


protected:
    bool onEvent(TRIGGER_TYPE);
    bool doAction(const Event& e);

signals:
    void alertGM(QString message);
    void alertOwner(QString message);
    void alertPlayers(QString message, PlayerPatern patern);
    void alertAllPlayers(QString message);

protected:

    void loadEvents();

    QString m_name;
    QString m_infos;
    QDomDocument m_dom;
    bool m_isSynced;

    QMultiMap<TRIGGER_TYPE, Event> m_eventMap;
};

#endif // XMLOBJECT_H
