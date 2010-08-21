#include <QtCore/QCoreApplication>
#include "person.h"
#include "object.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Object obj("test.xml");
    Object to;
    to.unserialiseXMLDocument(obj.serialiseXMLDocument());
    to.throwUp();
    return a.exec();
}
