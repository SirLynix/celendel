#ifndef NETWORK_H
#define NETWORK_H

#include <QCoreApplication>
#define qCApp QCoreApplication::instance()
#include <QtNetwork>

#include "Client.h"

class Packet;

void log(const QString txt, bool time=true); //Write a log in console with date and time.

class ServerNetwork : public QObject
{
    Q_OBJECT

    public:
        ServerNetwork(QObject* parent=NULL);
        ~ServerNetwork();

    public slots:
        bool sendToClient(CLID ID, Packet* pa, bool delegateDelete=true); //Send a packet to a client - return true if the client is not found
        void sendToAll(Packet* pa, bool delegateDelete=true); //Send a packet to all

        bool sendToClient(CLID ID, qint32 type, const QByteArray& data, qint32 ts=-1); //Overloaded functions for convenience.
        void sendToAll(qint32 type, const QByteArray& data, qint32 ts=-1);

    private slots:
        void newConnection(); //Called when someone ask for connection
        void clientDisconnected(); //Called when someone is disconnected
        void slot_dataReceived(Packet*); //Called when a client has send a FULL packet

    signals:
        void newClient(CLID ID);
        void clientGone(CLID ID);

        void dataReceived(Packet*, CLID who);

    private:
        QTcpServer* m_server;
        QList<Client*> m_clients;

};

#endif
