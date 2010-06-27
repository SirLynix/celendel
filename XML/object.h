#ifndef OBJECT_H
#define OBJECT_H
#include "XMLObject.h"

class Object : public XMLObject
{
Q_OBJECT
public:
    Object();
    //~Object();

public slots:
    bool throwUp();
    bool give();

private:
    unsigned int m_weight;
    //Person *m_owner;


};

#endif // OBJECT_H
