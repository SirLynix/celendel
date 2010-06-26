#include "Server.h"
#include <QTimer>

Server::Server(QObject* parent) : QObject(parent)
{
    m_network=new ServerNetwork(this); //Start the network


    /*QTimer *timer = new QTimer(this); //Just some bullshit for tests
    timer->setSingleShot(true);
    timer->start(5000);
    connect(timer, SIGNAL(timeout()), qCApp, SLOT(quit()));*/
}


