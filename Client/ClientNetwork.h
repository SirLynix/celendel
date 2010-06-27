#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <QTcpSocket>
#include "..\Shared\Constants.h"
#include "..\Shared\Packet.h"

class ClientNetwork : public QObject
{
    Q_OBJECT
    public:
        ClientNetwork(QObject* parent=NULL);
        ~ClientNetwork();

    public slots:
        void send(Packet* pa, bool delegateDelete=true);

        void send(Packet& pa); //Overload functions for convenience.
        void send(qint32 type, const QByteArray& data);

    private slots:
        void connected();
        void disconnected();
        void dataReceived();
        void socketError(QAbstractSocket::SocketError);

    signals:
        void packetReceived(Packet*);

    private:
        QTcpSocket* m_socket;
        Packet *packet;

};

#endif
