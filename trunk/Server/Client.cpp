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
    connect(m_securityTimer, SIGNAL(timeout()), this, SLOT(resetSecurity()));
    m_blamesTimer=new QTimer(this);
    m_blamesTimer->start(BLAMES_RESET_DELAY);
    m_blames=0;
    connect(m_blamesTimer, SIGNAL(timeout()), this, SLOT(resetBlames()));

}

void Client::changeID()
{
    ++cID;
    if(cID<1)
        cID=1;

    m_ID=cID;
}

bool Client::blame()
{
 ++m_blames;
 qDebug() << "Blamed";
 if(m_blames>=MAX_BLAMES)
 {
     qDebug() << "WARNING : Client reached the blames limit ! Abording connection !"; //What happenned ? Is the client corrupted ? Are the protocols differents ? Is the client attacking the server ?
     socket->abort();
     return true;
 }
 return false;
}

void Client::resetBlames()
{
    m_blames=0;
}

void Client::resetSecurity()
{
    m_sequentialsPackets=0;
}

void Client::readyRead()
{
    if(socket->state()!=QAbstractSocket::ConnectedState)
    {
        qDebug() << "Data received... but the Client is NOT connected... WTF ?";
        return;
    }

    m_securityTimer->start(PACKETS_COUNT_RESET_DELAY);
    QDataStream in(socket);

    if (packet == NULL)//Try to get the header
    {
        if (socket->bytesAvailable() < (int)sizeofheader) //The header is not here yet
             return;

        packet = new Packet();
        packet->setHeader(in);
        if(packet->dataSize > MAX_PACKET_SIZE) //A legal packet will NEVER be bigger than 1Mio, else it's an attack.
        {
            qDebug() << "ERROR : packet too big. Connection aborded.";
            socket->abort(); // ... and guess what we do to crackers...
            delete packet;
            packet=NULL;
            return;
        }

        if(packet->error())
        {
            qDebug() << "HOLY SHIT, packet error in header ! What I am supposed to do ?";
            delete packet;
            packet=NULL;
            return;
        }
    }

    if (socket->bytesAvailable() < packet->dataSize) //Try to get the body
        return;

    packet->setBody(in);

    if(packet->error())
    {
        qDebug() << "Packet error at Client reception level... Signal NOT emited";
        delete packet;
        packet=NULL;
        qDebug() << "Packet deleted... Without segfault !";
        blame();
        return;
    }
    else
    {
        emit dataReceived(packet);
    }

    packet=NULL;
    ++m_sequentialsPackets;

    if(m_sequentialsPackets>=MAX_SEQUENTIALS_PACKETS)//A legal client will NEVER send so much sequentials packet. It's probably an attack.
    {
        qDebug() << "Error, too much packets. Client will be kicked.";
        socket->abort(); // So, seeya pirate !
        return;
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
