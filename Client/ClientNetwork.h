#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <QMap>
#include <QTcpSocket>
#include <QStringList>
#include <QTimer>
#include "..\Shared\Constants.h"
#include "..\Shared\Packet.h"


class ClientNetwork : public QObject
{
    Q_OBJECT
    public:
        ClientNetwork(QString IP, quint16 port, QObject* parent=NULL);
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
        void disconnection();

        bool setServer(QString IP, quint16 port); //True on error (connection already etablished - disconnect first)

    private slots:
        void connected();
        void disconnected();
        void dataReceived();
        void socketError(QAbstractSocket::SocketError);

        void operatePacket(Packet* packet);

    signals:
        void packetReceived();
        void packetCorrupted();
        void pingUpdated(quint32);
        void chatReceived(CLID sender, QString lang, QString text, ENUM_TYPE canal);
        void serverInformationsChanged(ServerInformations);
        void clientIDChanged(CLID);
        void nicknameChanged(CLID, QString);
        void error(ENUM_TYPE, QString);
        void clientVoted(CLID f, CLID t);
        void newGameMaster(CLID);
        void serverName(QString);
        void motdChanged(QString);
        void gameLaunched();
        void narrationChanged(QString);
        void mapChanged(MapPtr);

        void mapFlare(QPoint,CLID);

        void scriptToGMMsg(QString ent, QString txt);
        void scriptToOwnerMsg(QString ent, QString txt);
        void scriptActionMsg(QString ent, QString txt);
        void scriptToPlayerMsg(QString ent, QString txt);
        void scriptMsg(QString ent, QString txt);
        void scriptError(QString ent, QString txt);

        void updateEntities(const QList<EntityInformations>&);
        void updateEntity(const EntityInformations&);
        void entityDeleted(const QString&);

        void scriptReceived(QString name, QString content);

        void ressourcesUpdated(const QMap<QString, RSID>& rss);

        void connectionEtablished();
        void connectionLost();
        void diceRolled(CLID, quint16, quint16);
        void sanctionned(CLID, ENUM_TYPE, QString);

        void clientJoined(CLID, QString);
        void clientLeft(CLID);

        void playSound(QString,QString);

        void syncLibs(QList<SoundLibInformations>);
        void syncLanguagesList(QList<QPair<QString, QString> >);
        void syncDictionariesList(QStringList list);

        void syncScriptList(QStringList list);

        void updateCharacterList(const QStringList& list);

    private:
        QTcpSocket* m_socket;
        Packet *packet;

        qint32 m_ping;

        QTimer *pingTimer;
        QTimer *flushTimer;

        QString m_serverIP;
        quint16 m_serverPort;

};

#endif
