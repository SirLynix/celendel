#include <iostream>
#include "Server.h"

int main(int argv, char** argc)
{
    // The more complex become an application, the smaller get it main
    //    - Me, right now.
    QCoreApplication app (argv, argc);

    Server server(&app);

    return app.exec();
}
