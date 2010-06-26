#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

#define CLID quint32 /// Alias for Client ID.

#include "../Shared/Packet.h"

class Client : public QObject
{
    Q_OBJECT
    public:
    Client(QTcpSocket *s);
    QTcpSocket* socket;
    Packet *packet;

    CLID ID () const {return m_ID;}

    signals:
        void dataReceived(Packet*);
        void disconnected();

    public slots:
        void send(Packet* pa);

    private slots:
        void readyRead();
        void slot_disconnected() { emit disconnected(); }

    private:
        CLID m_ID;
};

#endif // CLIENT_H
