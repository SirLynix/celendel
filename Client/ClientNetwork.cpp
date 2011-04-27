#include "ClientNetwork.h"

#include <QDebug>
#include <QDateTime>
#include "../Shared/Serializer.h"
#include <QHostAddress>

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


ClientNetwork::ClientNetwork(QString IP, quint16 port, QObject* par):QObject(par)
{
    m_socket=new QTcpSocket(this);

    m_serverIP=IP;
    m_serverPort=port;

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

    packet=NULL;

    pingTimer=new QTimer(this);

    pingTimer->setSingleShot(false);
    connect(pingTimer, SIGNAL(timeout()), this, SLOT(ping()));

    flushTimer=new QTimer(this);

    flushTimer->setSingleShot(false);
    connect(flushTimer, SIGNAL(timeout()), this, SLOT(flush()));

    connection();
}

bool ClientNetwork::setServer(QString IP, quint16 port)
{
    if(isConnected())
        return true;

    m_serverIP=IP;
    m_serverPort=port;

    return false;
}

QString ClientNetwork::serverIP() const
{
    if(!isConnected())
        return m_serverIP;
    return m_socket->peerAddress().toString();
}

quint16 ClientNetwork::serverPort() const
{
    if(!isConnected())
        return m_serverPort;
    return m_socket->peerPort();
}

void ClientNetwork::connection()
{
    m_socket->abort();
    m_socket->connectToHost(m_serverIP, m_serverPort);
}

void ClientNetwork::disconnection()
{
    m_socket->disconnectFromHost();
}

bool ClientNetwork::isConnected() const
{
    return m_socket->state()==QAbstractSocket::ConnectedState;
}

ClientNetwork::~ClientNetwork()
{
    m_socket->disconnectFromHost();
}

void ClientNetwork::flush() //Depreciated
{
    /*m_socket->flush();
    dataReceived();*/
}

void ClientNetwork::connected()
{
    emit connectionEtablished();

    pingTimer->start(10000);
    flushTimer->start(100);
    ping();
}

void ClientNetwork::disconnected()
{
    emit connectionLost();

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
    forever
    {
    QDataStream in(m_socket);

    if (packet == NULL)//Try to get the header
    {
        if (m_socket->bytesAvailable() < static_cast<int>(sizeofheader)) //The header is not here yet
             return;

        packet = new Packet();
        packet->setHeader(in);
    }

    if (m_socket->bytesAvailable() < packet->dataSize) //Try to get the body
        return;

    packet->setBody(in);


    operatePacket(packet);

    emit packetReceived();

    delete packet;

    packet=NULL;
    }
}

void ClientNetwork::socketError(QAbstractSocket::SocketError)
{
    log("Error : " + m_socket->errorString());
}

