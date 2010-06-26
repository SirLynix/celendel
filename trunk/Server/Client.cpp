#include "Client.h"
#include <QByteArray>

Client::Client(QTcpSocket *s) : socket(s), packet(NULL)
{
    static CLID cID=0;
    m_ID=cID;
    ++cID;

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
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

void Client::send(Packet* pa)
{
    QByteArray ba;
    pa->serialise(ba);
    socket->write(ba);
}
