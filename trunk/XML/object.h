#ifndef OBJECT_H
#define OBJECT_H
#include "person.h"

class Object : public XMLObject
{
Q_OBJECT
public:
    Object();
    Object(QString name, int weight, QString infos);

   void save(QTextStream& fileTxtStr);
   bool save(QString filename);

public slots:
    bool throwUp();
    bool give(Person *target);

private:
    unsigned int m_weight;
    Person *m_owner;


};

#endif // OBJECT_H
