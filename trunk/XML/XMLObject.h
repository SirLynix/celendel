#ifndef XMLOBJECT_H
#define XMLOBJECT_H
#include <QString>
#include <QObject>
#include <QMultiMap>
#include <QtXml/QtXml>

enum TRIGGER_TYPE {NOT_A_TRIGGER, ON_CREATION, ON_DESTRUCTION, ON_THROWN, ON_EQUIPPED, ON_OWNER_CHANGE, ON_USE, REGULAR};
enum ACTION_TYPE {NOT_AN_ACTION, ALERT_GM, ALERT_ALL_PLAYERS, ALERT_OWNER, ALERT_SPECIAL_PLAYER, FEED, DAMAGE, DESTROY, USE_OBJECT};

TRIGGER_TYPE stringToTrigger(const QString& s);
ACTION_TYPE stringToAction(const QString& s);
QString triggerToString(TRIGGER_TYPE s);
QString actionToString(ACTION_TYPE s);
QMultiMap<QString,QString> extractElementAttributes(const QDomElement& e);

struct PlayerPatern
{
    PlayerPatern():human(false) {}
    QString nameRegExp;
    QString classRegExp;
    bool human;
};

struct ObjectPatern
{
    PlayerPatern owner;
    QString nameRegExp;
};

struct Amount
{
    Amount(int _a=0,int _b=0, int _c=0):a(_a), b(_b), c(_c) {}
    int a;
    int b;
    int c;
    QList<int> array;
};

struct Event
{
    Event(ACTION_TYPE act=NOT_AN_ACTION) : randomFactor(0), action(act) { data.ptr=NULL; }
    bool isValid() const { return action!=NOT_AN_ACTION; }
    QString name;
    unsigned int randomFactor;
    ACTION_TYPE action;
    QString text;
    union {void* ptr; PlayerPatern* plyPatern; Amount* amount; ObjectPatern* objPatern;} data;
};

class XMLObject : public QObject
{
Q_OBJECT
public:
    XMLObject();
    ~XMLObject();

    QString getName() const { return m_name; }

    bool unserialiseXMLDocument(const QByteArray& b);
    QByteArray serialiseXMLDocument();

   bool save(const QString& filename); //True on error
   bool load(const QString& filename, bool forceLoading=false); //True on error
   bool loadFromMemory(const QByteArray& data, bool forceLoading=false); //True on error

   bool error() const {return m_error;}

   uint life() const {return m_life;}
   bool isDestroyable() const {return m_destroyable;}
   bool isDestroyed() const {return m_life==0;}

   void damage(uint dmg);

   bool use(bool isScript=false);

signals:
    void alertGM(QString message);
    void alertOwner(QString message);
    void alertPlayers(QString message, PlayerPatern patern);
    void alertAllPlayers(QString message);

    void useObject(ObjectPatern patern);

    void destroyed(int damage);
    void damaged(int damage);

    void used(bool isScript);

private:
    void loadEvents();

protected:

    QString synchronise(); //Rebuild the XML document in RAM, from the others RAM data

    virtual bool loadCustomData() = 0; //Overload this function for custom data loading from file - it will be called BEFORE the 'ON_CREATION' trigger
    virtual void synchroniseCustomData(QString&) = 0;

    bool onEvent(TRIGGER_TYPE);
    bool doAction(const Event& e);

    bool m_error;

    QString m_typePrefix;
    QString m_name;
    QString m_infos;
    QDomDocument m_dom;
    bool m_isSynced;

    uint m_life;
    bool m_destroyable;

    QMultiMap<TRIGGER_TYPE, Event> m_eventMap;
};

#endif // XMLOBJECT_H
