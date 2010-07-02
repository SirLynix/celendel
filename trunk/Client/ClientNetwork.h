#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <QMap>
#include <QTcpSocket>
#include <QTimer>
#include "..\Shared\Constants.h"
#include "..\Shared\Packet.h"

class ClientNetwork : public QObject
{
    Q_OBJECT
    public:
        ClientNetwork(QObject* parent=NULL);
        ~ClientNetwork();

        bool isConnected() const;

    public slots:
        void send(Packet* pa, bool delegateDelete=true);

        void send(Packet& pa); //Overloaded functions for convenience.
        void send(qint32 type, const QByteArray& data);

        void ping();
        qint32 getPing() const {return m_ping;}

        QString serverIP() const;
        quint16 serverPort() const;

        void flush();

        void connection();

    private slots:
        void connected();
        void disconnected();
        void dataReceived();
        void socketError(QAbstractSocket::SocketError);

        void operatePacket(Packet* packet);

    signals:
        void packetReceived();
        void pingUpdated(quint32);
        void chatReceived(CLID sender, QString text, ENUM_TYPE canal);
        void serverInformationsChanged(ServerInformations);
        void clientIDChanged(CLID);
        void nicknameChanged(CLID, QString);
        void error(ENUM_TYPE, QString);
        void clientVoted(CLID f, CLID t);
        void newGameMaster(CLID);
        void serverName(QString);
        void gameLaunched();

        void connectionEtablished();
        void connectionLost();
        void diceRolled(CLID, quint16);
        void sanctionned(CLID, ENUM_TYPE, QString);

        void clientJoined(CLID);
        void clientLeft(CLID);

    private:
        QTcpSocket* m_socket;
        Packet *packet;

        qint32 m_ping;

        QTimer *pingTimer;
        QTimer *flushTimer;

};

#endif
