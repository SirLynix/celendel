#ifndef PERSON_H
#define PERSON_H
#include "XMLObject.h"

enum BEHAVIOR_TYPE {BH_PLAYER, BH_ENNEMY, BH_AGGRESSIVE, BH_UNKNOWN };

class person : public XMLObject
{
public:
    person();

private:
   bool damage(unsigned int damage);
   bool heal(unsigned int amount = 0);

   int m_vie;
   BEHAVIOR_TYPE m_behavior;
};

#endif // PERSON_H
