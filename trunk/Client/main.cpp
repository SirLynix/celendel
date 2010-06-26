#include <iostream>
#include <QCoreApplication>
#include "ClientNetwork.h"

int main(int argv, char** argc)
{
    QCoreApplication app (argv, argc);

    std::cout << "Celendel client network launched" << std::endl;

    ClientNetwork cli(&app);

    return app.exec();
}
