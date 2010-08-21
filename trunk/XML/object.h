#ifndef OBJECT_H
#define OBJECT_H
#include "person.h"

enum OBJECT_CLASS {OTHER, SIMPLE_OBJECT, OH_WEAPON, TH_WEAPON, SHOULDER_PIECE, HELMET, TORSO_PIECE, GLOVES, ARMS_PIECE, LEGS_PIECE, BOOTS, UNDERWEAR, CONSUMMABLE, RINGS, AMULET, ARTIFACTS};

class Object : public XMLObject
{
    Q_OBJECT
    public:
        Object(const QString& filename);
        Object(int weight=1, const QString& name="", const QString& infos = "");
        Object(const Object& obj);

        bool matchPatern(const ObjectPatern& patern);

    public slots:
        bool throwUp();
        bool give(Person *target);

    protected:

        bool loadCustomData();
        void synchroniseCustomData(QString&);

        bool onEvent(TRIGGER_TYPE);

    private:
        unsigned int m_weight;
        Person *m_owner;
        OBJECT_CLASS m_class;
        QString m_customType;
};

#endif // OBJECT_H
