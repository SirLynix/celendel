#include <QtCore/QCoreApplication>
#include "person.h"
#include "object.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Object obj("test.xml");
    obj.throwUp();
    return a.exec();
}
