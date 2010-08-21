#ifndef PERSON_H
#define PERSON_H
#include "XMLObject.h"

enum BEHAVIOR_TYPE {BH_PLAYER, BH_ENNEMY, BH_AGGRESSIVE, BH_UNKNOWN};

class Person : public XMLObject
{
    Q_OBJECT
    public:
        Person(const QString& filename = "", const QString& name = "", BEHAVIOR_TYPE bh = BH_UNKNOWN, const QString& infos = "");

        bool matchPatern(const PlayerPatern& patern);

    protected:
        bool loadCustomData();
        void synchroniseCustomData(QString&);

    private:

       BEHAVIOR_TYPE m_behavior;
       QString m_class;
};

#endif // PERSON_H
