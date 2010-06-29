#include <QtCore/QCoreApplication>
#include "person.h"
#include "object.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Person personnage;
    Object objet;

    objet.give(&personnage);
    objet.save("objet.xml");

    return a.exec();
}
