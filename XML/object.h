#ifndef OBJECT_H
#define OBJECT_H
#include "person.h"

class Object : public XMLObject
{
Q_OBJECT
public:
    Object(const QString& filename);
    Object(int weight=1, const QString& name="", const QString& infos = "");

public slots:
    bool throwUp();
    bool give(Person *target);

private:
    unsigned int m_weight;
    Person *m_owner;
    //void baseDoc();


};

#endif // OBJECT_H
