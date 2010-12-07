#include <iostream>
#include "Server.h"

int main(int argv, char** argc)
{
    QCoreApplication app (argv, argc);

    Translator t;
    t.loadLanguage("Elfic", "dictionaries/elfic.dic");
    qDebug() << t.translate("Je suis une phrase !", "Elfic", 50);

    std::cout << "Celendel server launched" << std::endl;

    Server server(&app);

    return app.exec();
}
