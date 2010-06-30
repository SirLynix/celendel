#include <iostream>
#include <QApplication>
#include "ClientInterface.h"

int main(int argv, char** argc)
{
    QApplication app (argv, argc);

    QTranslator qtTranslator;
     qtTranslator.load("qt_" + QLocale::system().name(),
             QLibraryInfo::location(QLibraryInfo::TranslationsPath));
     app.installTranslator(&qtTranslator);

     QTranslator myappTranslator;
     myappTranslator.load("myapp_" + QLocale::system().name());
     app.installTranslator(&myappTranslator);


    ClientInterface cl;
    cl.show();

    return app.exec();
}
