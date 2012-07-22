#include <iostream>
#include "Server.h"

int main(int argv, char** argc)
{
    // The more complex an application become, the smaller its main() gets
    //    - Me, right now.
    QCoreApplication app (argv, argc);

    Server server(&app);

    return app.exec();
}
