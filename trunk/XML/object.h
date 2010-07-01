#ifndef OBJECT_H
#define OBJECT_H
#include "person.h"

class Object : public XMLObject
{
Q_OBJECT
public:
    Object(QString filename = "",QString name = "", int weight = 1, QString infos = "");

public slots:
    bool throwUp();
    bool give(Person *target);

private:
    unsigned int m_weight;
    Person *m_owner;
    void baseDoc();


};

#endif // OBJECT_H
