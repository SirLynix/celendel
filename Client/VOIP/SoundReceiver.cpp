#include "SoundReceiver.h"

namespace VOIPSystem
{

SoundReceiver::SoundReceiver(const QHostAddress& hostAddress, const quint16& port, int sampleRate) : speex(sampleRate)
{
    udpSocket = new QUdpSocket(this);
    m_IP=hostAddress;
    setPort(port);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    connect(&speex, SIGNAL(decoded(ALshortVector)), this, SLOT(decoded(ALshortVector)), Qt::QueuedConnection);

    QTimer *updateTimer = new QTimer(this);

    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    updateTimer->start(500);

    dta=0;
    DPS=0;
}

void SoundReceiver::setPort(quint16 port)
{
    udpSocket->bind(m_IP, port, QUdpSocket::ShareAddress);
}

void SoundReceiver::update()
{
    DPS=dta*2;
    dta=0;
}

int SoundReceiver::dataPerSecond()
{
    return DPS;
}

void SoundReceiver::decoded(const ALshortVector& samples)
{
    if(samples.size())
        emit dataReceived(samples);
}

void SoundReceiver::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sendr;
        quint16 senderPort;
        udpSocket->readDatagram(datagram.data(), datagram.size(), &sendr, &senderPort);
        dta += datagram.size();

        speex.decode(datagram);
    }
}
}
