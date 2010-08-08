#include <QtCore/QCoreApplication>
#include "person.h"
#include "object.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    XMLObject obj;
    obj.load("test.xml");

    return a.exec();
}
