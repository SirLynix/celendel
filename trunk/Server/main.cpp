#include <iostream>
#include "Server.h"

int main(int argv, char** argc)
{
    QCoreApplication app (argv, argc);

    std::cout << "Celendel server launched" << std::endl;

    Server server(&app);

    return app.exec();
}
