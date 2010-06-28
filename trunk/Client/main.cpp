#include <iostream>
#include <QApplication>
#include "ClientInterface.h"

int main(int argv, char** argc)
{
    QApplication app (argv, argc);

    ClientInterface cl;
    cl.show();

    return app.exec();
}
