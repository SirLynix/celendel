#include <QtCore/QCoreApplication>
#include "person.h"
#include "object.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Object obj;
    obj.load("test.xml");
    obj.throwUp();
    return a.exec();
}
