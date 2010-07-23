#include "VOIP.h"

using namespace VOIPSystem;
/*
VOIP& getVOIP()
{
    static VOIP voip;
    return voip;
}*/

VOIPThread& getVOIP()
{
    static VOIPThread voip;
    return voip;
}

VOIPThread::VOIPThread(QObject* p): QThread(p)
{
    t=NULL;
    m_voip=new VOIP();
    start();
    while(t==NULL) { mutex.lock(); msleep(1); mutex.unlock();}
    mutex.lock();
    m_voip->moveToThread(t);
    t=NULL;
    mutex.unlock();
}

void VOIPThread::run()
{
    mutex.lock();
    t=this;
    mutex.unlock();
    while(t!=NULL) { mutex.lock(); msleep(1); mutex.unlock(); }

    mutex.lock();
    m_voip->setParent(this);

    connect(m_voip, SIGNAL(dataPerSecond(int, int)), this, SLOT(dtaPS(int,int)),Qt::QueuedConnection);
    mutex.unlock();

    exec();
}

VOIPThread::~VOIPThread()
{
    quit();
    mutex.lock();
    delete m_voip;
    m_voip=NULL;
    mutex.unlock();
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
    setVolume(50);
    m_enabled=true;
    setQuality(4);
}

void VOIP::setVolume(float volume)
{
    if(volume<0)
    {
        m_volume=0;
    }
    else if(volume>100)
    {
        m_volume=1;
    }
    else
        m_volume=volume/100;

    for(int i=0;i<m_sounds.size();++i)
        m_sounds[i]->volume(volume);
}

void VOIP::setEnabled(bool e)
{
    m_enabled=e;

    for(int i=0;i<m_sounds.size();++i)
    {
        if(!m_enabled)
        {
            m_sounds[i]->mute();
        }
        else
            m_sounds[i]->unmute();
    }
}

void VOIP::setQuality(float q)
{
    if(q>10)
        q=10;
    if(q<0)
        q=0;

    speex.setQuality(q);

    if(q>7)
    {
        m_floor=20;
    }
    else if(q>5)
    {
        m_floor=15;
    }
    else if(q>3)
    {
        m_floor=9;
    }
    else if(q>2)
    {
        m_floor=6;
    }
    else
    {
        m_floor=1;
    }
}

void VOIP::send(QByteArray b)
{
    if(b.size() > m_floor && m_enabled)
    {
        for(int i = 0; i < m_clients.size(); ++i)
        {
            udpSocket->writeDatagram(b, b.size(), QHostAddress(m_clients.at(i)), VOIP_PORT);
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
    m_receivers.append(new SoundReceiver(QHostAddress(cl), VOIP_PORT, SAMPLE_RATE));
    m_sounds.append(new Sound(SAMPLE_RATE));
    m_sounds.last()->volume(m_volume);
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
