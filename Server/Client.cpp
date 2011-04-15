#include "Client.h"
#include <QByteArray>

CLID Client::cID=0;

Client::Client(QTcpSocket *s) : socket(s), packet(NULL)
{
    changeID();

    socket->setReadBufferSize(SOCKET_BUFFER_SIZE);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(slot_disconnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

    m_securityTimer=new QTimer(this);
    m_securityTimer->start(PACKETS_COUNT_RESET_DELAY);
    m_sequentialsPackets=0;
    connect(m_securityTimer, SIGNAL(timeout()), this, SLOT(resetSecurity()));
}

void Client::error(QAbstractSocket::SocketError socketError)
{
    if(socketError!=QAbstractSocket::RemoteHostClosedError)
    {
        qDebug() << "An error happened ! HELP ! " << socket->errorString();
        socket->abort();
    }
}

void Client::changeID()
{
    ++cID;
    if(cID<1)
        cID=1;

    m_ID=cID;
}

void Client::blame()
{
    qDebug() << "WARNING : Server requested a blame against a client ! Abording connection !";
    socket->abort();

}

void Client::resetSecurity()
{
    m_sequentialsPackets=0;
}

void Client::readyRead()
{
    forever
    {
    if(socket->state()!=QAbstractSocket::ConnectedState||!socket->isValid())
    {
        qDebug() << "Data received... but the Client is NOT connected... WTF ?";
        return;
    }

    m_securityTimer->start(PACKETS_COUNT_RESET_DELAY);
    QDataStream in(socket);

    if (packet.get()==NULL)//Try to get the header
    {
        if (socket->bytesAvailable() < static_cast<qint64>(sizeofheader)) //The header is not here yet
             return;

        packet.reset(new Packet());

        packet->setHeader(in);
        if(packet->dataSize > MAX_PACKET_SIZE) //A legal packet will NEVER be bigger than 1Mio, else it's an attack.
        {
            qDebug() << "ERROR : packet too big. Connection aborded.";
            blame(); // ... and guess what we do to crackers...
            return;
        }

        if(packet->error())
        {
            qDebug() << "HOLY SHIT, packet error in header ! What I am supposed to do ?";
            blame();
            return;
        }
    }

    if (socket->bytesAvailable() < packet->dataSize) //Try to get the body
        return;

    packet->setBody(in);

    if(packet->error())
    {
        qDebug() << "Packet error at Client reception level... Signal NOT emited";
        blame();
        return;
    }
    else
    {
        emit dataReceived(packet);
    }

    packet.reset();
    ++m_sequentialsPackets;

    if(m_sequentialsPackets>=MAX_SEQUENTIALS_PACKETS)//A legal client will NEVER send so much sequentials packet. It's probably an attack.
    {
        qDebug() << "Error, too much packets. Client will be kicked.";
        blame(); // So, seeya pirate !
        return;
    }
    }
}

void Client::send(Packet& pa)
{
    send(&pa);
}

void Client::flush()
{
   /* socket->flush();
    readyRead();*/
}

void Client::send(Packet* pa)
{
    QByteArray ba;
    pa->serialise(ba);
    socket->write(ba);
    flush();
}
