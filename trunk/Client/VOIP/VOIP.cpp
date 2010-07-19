#include "VOIP.h"

using namespace VOIPSystem;

VOIP& getVOIP()
{
    static VOIP voip;
    return voip;
}

VOIP::VOIP(QObject* p) : QObject(p), speex(SAMPLE_RATE)
{
    qRegisterMetaType<ALshortVector >();
    rec = new Recorder(SAMPLE_RATE, this);
    rec->startRecord();
    connect(rec, SIGNAL(readyRead(ALshortVector)), &speex, SLOT(encode(ALshortVector)), Qt::QueuedConnection);
    connect(&speex, SIGNAL(encoded(QByteArray)), this, SLOT(send(QByteArray)), Qt::QueuedConnection);
    QTimer* updateT = new QTimer(this);
    connect(updateT, SIGNAL(timeout()), this, SLOT(update()));
    updateT->start(1000);
    udpSocket = new QUdpSocket(this);
    dataUp = 0;
}

void VOIP::setQuality(int q)
{
    speex.setQuality(q);
}

int VOIP::quality()
{
    return speex.quality();
}

void VOIP::send(QByteArray b)
{
    if(b.size() > 15)
    {
        for(int i = 0; i < m_clients.size(); ++i)
        {
            qDebug() << "Send" << m_clients.at(i) << "\t" << b.size();
            udpSocket->writeDatagram(b, b.size(), QHostAddress(m_clients.at(i)), PORT);
            dataUp += b.size();
        }
    }
}

void VOIP::update()
{
    int d = 0;
    for(size_t i = 0; i < (size_t)m_clients.size(); ++i)
    {
        d += m_receivers.at(i)->dataPerSecond();
    }
    emit dataPerSecond(d, dataUp);
    dataUp = 0;
}

VOIP::~VOIP()
{
    for(size_t i = 0; i < (size_t)m_receivers.size(); ++i)
    {
        delete m_receivers.at(i);
        delete m_sounds.at(i);
    }
}

void VOIP::add(const QString& cl)
{
    if(m_clients.contains(cl))
        remove(cl);

    m_clients.append(cl);
    m_receivers.append(new SoundReceiver(QHostAddress(cl), PORT, SAMPLE_RATE));
    m_sounds.append(new Sound(SAMPLE_RATE));
    connect(m_receivers.last(), SIGNAL(dataReceived(const ALshortVector&)), m_sounds.last(), SLOT(queue(const ALshortVector&)));
    m_sounds.last()->play();
}

void VOIP::removeAll()
{
    for(int i = 0; i < m_clients.size(); ++i)
    {
        remove(m_clients.at(i));
    }
}

bool VOIP::mute(const QString& cl)
{
    if(!m_clients.contains(cl))
        return true;

    m_sounds.at(m_clients.indexOf(cl))->mute();
    return false;
}

bool VOIP::unmute(const QString& cl)
{
    if(!m_clients.contains(cl))
        return true;

    m_sounds.at(m_clients.indexOf(cl))->unmute();
    return false;
}

bool VOIP::remove(const QString& cl)
{
    if(!m_clients.contains(cl))
        return true;

    int index = m_clients.indexOf(cl);
    m_receivers.removeAt(index);
    m_sounds.removeAt(index);
    m_clients.removeAt(index);
    return false;
}
