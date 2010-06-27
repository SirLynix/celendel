#include "Client.h"
#include <QByteArray>

CLID Client::cID=0;

Client::Client(QTcpSocket *s) : socket(s), packet(NULL)
{
    m_ID=cID;
    ++cID;

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(slot_disconnected()));
}

void Client::changeID()
{
    m_ID=cID;
    ++cID;
}

void Client::readyRead()
{
    QDataStream in(socket);

    if (packet == NULL)//Try to get the header
    {
        if (socket->bytesAvailable() < (int)sizeof(qint32)*4) //The header is not here yet
             return;

        packet = new Packet();
        packet->setHeader(in);
    }

    if (socket->bytesAvailable() < packet->dataSize) //Try to get the body
        return;

    packet->setBody(in);

    emit dataReceived(packet);
    packet=NULL;
}

void Client::send(Packet& pa)
{
    send(&pa);
}

void Client::send(Packet* pa)
{
    QByteArray ba;
    pa->serialise(ba);
    socket->write(ba);
}
