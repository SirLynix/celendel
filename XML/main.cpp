#include <QtCore/QCoreApplication>
#include "person.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    person myObject;
    myObject.save("test.xml");

    return a.exec();
}
