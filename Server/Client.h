#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "..\Shared\Constants.h"

#include "../Shared/Packet.h"

#include <QTimer>

class Client : public QObject
{
    Q_OBJECT
    public:
    Client(QTcpSocket *s);
    QTcpSocket* socket;
    Packet *packet;

    CLID ID () const {return m_ID;}
    void changeID(); //Dangerous ! Only use at init

    signals:
        void dataReceived(Packet*);
        void disconnected();

    public slots:
        void send(Packet* pa);
        void send(Packet& pa);

        void flush();

        bool blame();

    private slots:
        void readyRead();
        void slot_disconnected() { emit disconnected(); }
        void resetSecurity();
        void resetBlames();

    private:
        CLID m_ID;
        static CLID cID;
        QTimer* m_securityTimer;
        quint16 m_sequentialsPackets;
        QTimer* m_blamesTimer;
        int m_blames;
};

#endif // CLIENT_H
