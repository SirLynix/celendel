#include "Client.h"
#include <QByteArray>

CLID Client::cID=0;

Client::Client(QTcpSocket *s) : socket(s), packet(NULL)
{
    changeID();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(slot_disconnected()));
    m_securityTimer=new QTimer(this);
    m_securityTimer->start(PACKETS_COUNT_RESET_DELAY);
    m_sequentialsPackets=0;
}

void Client::changeID()
{
    ++cID;
    if(cID<1)
        cID=1;

    m_ID=cID;
}

void Client::resetSecurity()
{
    m_sequentialsPackets=0;
}

void Client::readyRead()
{
    m_securityTimer->start(PACKETS_COUNT_RESET_DELAY);
    QDataStream in(socket);

    if (packet == NULL)//Try to get the header
    {
        if (socket->bytesAvailable() < (int)sizeof(qint32)*4) //The header is not here yet
             return;

        packet = new Packet();
        packet->setHeader(in);
        if(packet->dataSize > 1024*1024*1024) //A legal packet will NEVER be bigger than 1Mio, else it's an attack.
        {
            qDebug() << "Error, packet too big. Client will be kicked.";
            socket->abort(); // ... and guess what we do to crackers...
        }
    }

    if (socket->bytesAvailable() < packet->dataSize) //Try to get the body
        return;

    packet->setBody(in);

    emit dataReceived(packet);
    packet=NULL;
    ++m_sequentialsPackets;

    if(m_sequentialsPackets>=MAX_SEQUENTIALS_PACKETS)//A legal client will NEVER send so much sequentials packet. It's probably an attack.
    {
        qDebug() << "Error, too much packets. Client will be kicked.";
        socket->abort(); // So, seeya pirate !
    }
}

void Client::send(Packet& pa)
{
    send(&pa);
}

void Client::flush()
{
    socket->flush();
    readyRead();
}

void Client::send(Packet* pa)
{
    QByteArray ba;
    pa->serialise(ba);
    socket->write(ba);
    flush();
}
