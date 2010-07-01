#ifndef PERSON_H
#define PERSON_H
#include "XMLObject.h"

enum BEHAVIOR_TYPE {BH_PLAYER, BH_ENNEMY, BH_AGGRESSIVE, BH_UNKNOWN };

class Person : public XMLObject
{
public:
    Person(QString filename = "",QString name = "", BEHAVIOR_TYPE bh = BH_UNKNOWN, QString infos = "");

private:
   bool damage(unsigned int damage);
   bool heal(unsigned int amount = 0);
   void baseDoc();

   int m_vie;
   BEHAVIOR_TYPE m_behavior;
};

#endif // PERSON_H
