#include "VOIPServer.h"

#include <QTimer>

#include <QDebug>

#define D() qDebug() << __FILE__ << ";" << __LINE__

VOIPServer::VOIPServer(QObject *par, quint16 incPort):QObject(par)
{
    m_udpSocket = new QUdpSocket(this);
    connect(m_udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

    m_udpSocket->bind(QHostAddress::Any, incPort, QUdpSocket::ShareAddress);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateStats()));
    timer->setSingleShot(false);
    timer->start(1000);

    m_dataDown=0;
    m_dataUp=0;
}


void VOIPServer::readPendingDatagrams()
{
    while (m_udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        QHostAddress sendr;
        quint16 senderPort;

        m_udpSocket->readDatagram(datagram.data(), datagram.size(), &sendr, &senderPort);
        m_dataDown += datagram.size();

        D();

        resend(sendr.toString(), datagram);
    }
}

void VOIPServer::resend(const QString& from, QByteArray& datagram)
{

    QStringList bl;
    if(m_blackList.contains(from))
        bl=m_blackList[from];

    QMap<QString, quint16>::const_iterator i = m_tgList.constBegin();
    while (i != m_tgList.constEnd())
    {
        if(!bl.contains(i.key()))
        {
            D();
            m_udpSocket->writeDatagram (datagram, QHostAddress(i.key()), i.value());
        }

        ++i;
    }
}

void VOIPServer::updateStats()
{
    emit statsUpdated(m_dataDown, m_dataUp);

    m_dataDown=0;
    m_dataUp=0;
}


void  VOIPServer::addTarget(const QString& IP, quint16 port)
{
    if(m_tgList.contains(IP))
        return;

    m_tgList[IP]=port;
}
void  VOIPServer::rmTarget(const QString& IP)
{
    m_tgList.remove(IP);
}

void VOIPServer::addBlacklist(const QString& toBL, const QString& who)
{
    if(toBL.isEmpty())
        return;


    if(!m_tgList.contains(who))
        return;

    if(!m_blackList[toBL].contains(who))
        m_blackList[toBL].append(who);


}
void VOIPServer::rmBlacklist(const QString& toBL, const QString& who)
{
    if(!m_blackList.contains(toBL))
        return;

    m_blackList[toBL].removeAll(who);
}

