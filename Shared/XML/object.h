#ifndef OBJECT_H
#define OBJECT_H
#include <boost/shared_ptr.hpp>
#include "MaterialThing.h"

enum OBJECT_CLASS {OTHER, SIMPLE_OBJECT, OH_WEAPON, TH_WEAPON, SHOULDER_PIECE, HELMET, TORSO_PIECE, GLOVES, ARMS_PIECE, LEGS_PIECE, BOOTS, UNDERWEAR, CONSUMMABLE, RINGS, AMULET, ARTIFACTS};

class Person;

class Object : public MaterialThing
{
    Q_OBJECT
    public:
        Object(const QString& filename);
        Object(int mass=1, const QString& name="", const QString& infos = "");
        Object(const Object& obj);

        ~Object();

        bool matchPatern(const ObjectPatern& patern);

    public slots:
        void throwUp();

    protected:

        bool loadCustomData();
        void synchroniseCustomData(QString&);

    private:

        void changeOwner(Person *owner);

        Person *m_owner;
        OBJECT_CLASS m_class;
        QString m_customType;

        friend class Person;
};

typedef boost::shared_ptr<Object> ObjectPtr;

#endif // OBJECT_H
