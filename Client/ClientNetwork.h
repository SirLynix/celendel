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

    public slots:
        void send(Packet* pa, bool delegateDelete=true);

        void send(Packet& pa); //Overloaded functions for convenience.
        void send(qint32 type, const QByteArray& data);

        void ping();
        qint32 getPing() const {return m_ping;}

    private slots:
        void connected();
        void disconnected();
        void dataReceived();
        void socketError(QAbstractSocket::SocketError);

        void flush();


    signals:
        void packetReceived(Packet*);
        void pingUpdated(quint32);

    private:
        QTcpSocket* m_socket;
        Packet *packet;

        bool m_gameStarted;
        CLID m_ID;
        CLID m_GMID;
        QString m_location;
        QString m_TOD;
        QString m_serverName;
        QMap<CLID, QString> m_nickMap;

        qint32 m_ping;

        QTimer *pingTimer;
        QTimer *flushTimer;

};

#endif
