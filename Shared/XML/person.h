#ifndef PERSON_H
#define PERSON_H
#include "MaterialThing.h"
#include "object.h"

enum BEHAVIOR_TYPE {BH_PLAYER, BH_ENNEMY, BH_AGGRESSIVE, BH_UNKNOWN};
QString BehaviorTypeToString(BEHAVIOR_TYPE);
BEHAVIOR_TYPE StringToBehaviorType(QString);


class Person : public MaterialThing
{
    Q_OBJECT
    public:
        Person(const QString& filename = "", const QString& name = "", BEHAVIOR_TYPE bh = BH_UNKNOWN, const QString& infos = "");

        bool matchPatern(const PlayerPatern& patern);

        ObjectPtr addObject(const QString&); //Add object in inventory - return true on error - do NOT duplicate objects - return a pointer on the created object
        ObjectPtr addObject(const ObjectPtr&);
        ObjectPtr addObject(Object*); //The ressource will be OWNED by this class. DO NOT DELETE THE RESSOURCE AFTER CALLING THIS METHOD, OR FACE THE CONSEQUENCES.
        ObjectPtr removeObject(const ObjectPtr&);

        const QList<ObjectPtr>& getInventoryList() const { return m_inventory; } //Return a copy (or a constant version) of the internal array of Object pointers.

    protected:
        bool loadCustomData();
        void synchroniseCustomData(QString&);

    private slots:
        void objectDestroyed();

    private:

       ObjectPtr getObjectSmartPtr(const Object* o) const;

       void removeObject(const Object*const); //Warning : the ressource is NOT deleted. Shall never be call unless by ~Object().
       friend Object::~Object();

       QList<ObjectPtr> m_inventory;

       QMap<QString, int> m_languages; //QString is the language name, int is the capacity to understand and speak this language (in percent)

       BEHAVIOR_TYPE m_behavior;
       QString m_class;
};

typedef boost::shared_ptr<Person> PersonPtr;

#endif // PERSON_H
