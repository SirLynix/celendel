#include "ClientNetwork.h"

#include <QDebug>
#include <QDateTime>

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
}

ClientNetwork::~ClientNetwork()
{
    m_socket->disconnectFromHost();
}

void ClientNetwork::connected()
{
    log("Connecte");
}

void ClientNetwork::disconnected()
{
    log("Deconnecte");
}

void ClientNetwork::dataReceived()
{
    QDataStream in(m_socket);

    if (packet == NULL)//Try to get the header
    {
        if (m_socket->bytesAvailable() < (int)sizeof(qint32)*4) //The header is not here yet
             return;

        packet = new Packet();
        packet->setHeader(in);
    }

    if (m_socket->bytesAvailable() < packet->dataSize) //Try to get the body
        return;

    packet->setBody(in);

    emit packetReceived(packet);
}

void ClientNetwork::socketError(QAbstractSocket::SocketError)
{
    log("Error : " + m_socket->errorString());
}

