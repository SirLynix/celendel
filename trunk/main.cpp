#include <QtCore/QCoreApplication>
#include "Object.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Object myObject;
    myObject.save("test.xml");

    return a.exec();
}
