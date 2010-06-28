#include "ClientNetwork.h"

#include <QDebug>
#include <QDateTime>
#include "..\Shared\Serializer.h"

void log(const QString txt, bool time = true);
void log(const QString txt, bool time)
{
    QString tmp;
    if(time)
    {
        tmp += QDateTime::currentDateTime().toString("dd/MM/yyyy - HH:mm:ss.zzz") + " : ";
    }
    tmp+=txt;
    qDebug(tmp.toAscii());
}


ClientNetwork::ClientNetwork(QObject* parent):QObject(parent)
{
    m_socket=new QTcpSocket(this);

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

    m_socket->connectToHost(SERVER_IP, SERVER_PORT);

    packet=NULL;
    m_ID=0;
    m_gameStarted=false;

    pingTimer=new QTimer(this);

    pingTimer->setSingleShot(false);
    connect(pingTimer, SIGNAL(timeout()), this, SLOT(ping()));

    flushTimer=new QTimer(this);

    flushTimer->setSingleShot(false);
    connect(flushTimer, SIGNAL(timeout()), this, SLOT(flush()));
}

ClientNetwork::~ClientNetwork()
{
    m_socket->disconnectFromHost();
}

void ClientNetwork::flush()
{
    m_socket->flush();
    dataReceived();
}

void ClientNetwork::connected()
{
    log("Connected");

    pingTimer->start(10000);
    flushTimer->start(100);

    ///Debug
    //send(ETI(CHAT), serialiseChatData(ETI(NORMAL), "Je suis une chaine."));
    //send(ETI(GM_ELECT), serialiseGMElectData(0));
    send(ETI(SET_NICK), serialiseSetNickData("Gigotdarnaud"));

}

void ClientNetwork::disconnected()
{
    log("Disconnected");
    pingTimer->stop();
    flushTimer->stop();
}

void ClientNetwork::send(Packet* pa, bool delegateDelete)
{
    QByteArray ba;
    pa->serialise(ba);
    m_socket->write(ba);
    m_socket->flush();

    if(delegateDelete)
        delete pa;
}

void ClientNetwork::send(Packet& pa)
{
    send(&pa, false);
}

void ClientNetwork::send(qint32 type, const QByteArray& data)
{
    Packet p;
    p.type=type;
    p.data=data;
    send(p);
}

void ClientNetwork::ping()
{
    send(ETI(PING), QByteArray());
}

void ClientNetwork::dataReceived()
{
    QDataStream in(m_socket);

    if (packet == NULL)//Try to get the header
    {
        if (m_socket->bytesAvailable() < (int)sizeofheader) //The header is not here yet
             return;

        packet = new Packet();
        packet->setHeader(in);
    }

    if (m_socket->bytesAvailable() < packet->dataSize) //Try to get the body
        return;

    packet->setBody(in);

    if(packet->type==PING) /// NOT DEBUG
    {
        m_ping=getTimeStamp()-packet->timestamp;
        emit pingUpdated(m_ping);
        qDebug() << "Ping = " << m_ping;
        delete packet;
        packet=NULL;
        return;
    }
    //packet->show(); ///Debug

    if(packet->type==MAP_INFORMATIONS)
    {
        qDebug() << "Map informations received.";
    }
    else if(packet->type==SERVER_INFORMATIONS)
    {
        ServerInformations si;
        extractServerInformationsData(packet->data, si);
        m_GMID=si.gameMasterID;
        m_location=si.location;
        m_TOD=si.timeOfDay;
        m_serverName=si.serverName;
        m_nickMap=si.playersName;
        m_gameStarted=si.gameStarted;
        qDebug() << "Server informations changed : " << si.gameMasterID << " " << m_nickMap;
    }
    else if(packet->type==SET_CLID) ///Debug
    {
        extractSetCLIDData(packet->data, m_ID);
        qDebug() << "ID changed : " << m_ID;
    }
    else if(packet->type==NEW_NICK) ///Debug
    {
        CLID nID; QString nick;
        extractNewNickData(packet->data, nID, nick);
        m_nickMap[nID]=nick;
        qDebug() << "Nick changed : " << nID << " = " << nick;
    }
    else if(packet->type==CHAT) ///Debug
    {
        QString txt;
        ENUM_TYPE can;
        extractChatData(packet->data, can, txt);

        qDebug()<<txt<<can;
    }
    else if(packet->type==NEW_GM) ///Debug
    {
        CLID gm;
        extractNewGMData(packet->data, gm);
        qDebug()<<gm;
    }
    else if(packet->type==VOTED) ///Debug
    {
        CLID f, t;
        extractVotedData(packet->data, f, t);
        qDebug()<<f<<" "<<t;
    }

    emit packetReceived(packet);
    delete packet; ///Debug

    packet=NULL;
}

void ClientNetwork::socketError(QAbstractSocket::SocketError)
{
    log("Error : " + m_socket->errorString());
}

