#ifndef PERSON_H
#define PERSON_H
#include "XMLObject.h"

enum BEHAVIOR_TYPE {BH_PLAYER, BH_ENNEMY, BH_AGGRESSIVE, BH_UNKNOWN };

class Person : public XMLObject
{
public:
    Person();
    Person(QString name, BEHAVIOR_TYPE bh, QString infos);

    void save(QTextStream& fileTxtStr);
    bool save(QString filename);

private:
   bool damage(unsigned int damage);
   bool heal(unsigned int amount = 0);

   int m_vie;
   BEHAVIOR_TYPE m_behavior;
};

#endif // PERSON_H
