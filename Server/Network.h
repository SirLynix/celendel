#ifndef NETWORK_H
#define NETWORK_H

#include <QCoreApplication>
#define qCApp QCoreApplication::instance()
#include <QtNetwork>

#define MAX_CLIENTS 100
#define SERVER_PORT 5577

#include "Client.h"

class Packet;

void log(const QString txt, bool time=true); //Write a log in console with date and time.

class ServerNetwork : public QObject
{
    Q_OBJECT

    public:
        ServerNetwork(QObject* parent=NULL);
        ~ServerNetwork();

    private slots:
        void newConnection(); //Called when someone ask for connection
        void clientDisconnected(); //Called when someone is disconnected
        void slot_dataReceived(Packet*); //Called when a client has send a FULL packet

        bool sendToClient(CLID ID, Packet* pa, bool delegateDelete=true); //Send a packet to a client - return true if the client is not found
        void sendToAll(Packet* pa, bool delegateDelete=true); //Send a packet to all

    signals:
        void newClient(CLID ID);
        void clientGone(CLID ID);

        void dataReceived(Packet*, quint32 who);

    private:
        QTcpServer* m_server;
        QList<Client*> m_clients;

};

#endif
