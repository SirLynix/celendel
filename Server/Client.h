#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "../Shared/Constants.h"

#include "../Shared/Packet.h"

#include <QTimer>
#include <memory>

class Client : public QObject
{
    Q_OBJECT
    public:
    Client(QTcpSocket *s);
    QTcpSocket* socket;
    std::auto_ptr<Packet> packet;

    CLID ID () const {return m_ID;}
    void changeID(); //Dangerous ! Only use at init

    signals:
        void dataReceived(std::auto_ptr<Packet>);
        void disconnected();

    public slots:
        void send(Packet* pa);
        void send(Packet& pa);

        void flush();

        void blame();

    private slots:
        void readyRead();
        void slot_disconnected() { emit disconnected(); }
        void resetSecurity();

        void error(QAbstractSocket::SocketError socketError);

    private:
        CLID m_ID;
        static CLID cID;
        QTimer* m_securityTimer;
        quint16 m_sequentialsPackets;
};

#endif // CLIENT_H
