#include "VOIP.h"

using namespace VOIPSystem;

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
    m_port=VOIP_DEFAULT_PORT;
}

VOIP::~VOIP()
{
    removeAll();
}

float VOIP::volume(const QString& ip) const
{
    int index;
    if(ip.isEmpty()||(index=indexOf(ip))==-1)
    {
        return m_volume;
    }
    else
    {
        return m_clients[index].sound->volume()*100;
    }
}

void VOIP::setVolume(float volume, const QString& ip)
{
    if(volume<0)
    {
        volume=0;
    }
    else if(volume>100)
    {
        volume=1;
    }
    else
        volume=volume/100;

    if(ip.isEmpty())
    {
        m_volume=volume;
        for(int i=0;i<m_clients.size();++i)
            m_clients[i].sound->setVolume(volume);
    }
    else
    {
        int in=indexOf(ip);
        if(in==-1)
            return;
        m_clients[in].sound->setVolume(volume);
    }
}

void VOIP::setEnabled(bool e)
{
    m_enabled=e;

    for(int i=0;i<m_clients.size();++i)
    {
        if(!m_enabled)
        {
            m_clients[i].sound->mute();
        }
        else
            m_clients[i].sound->unmute();
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
        for(int i=0;i<m_clients.size();++i)
        {
            udpSocket->writeDatagram(b, b.size(), QHostAddress(m_clients[i].IP), m_port);
            dataUp += b.size();
        }
    }
}

void VOIP::update()
{
    int d = 0;
    for(size_t i = 0; i < (size_t)m_clients.size(); ++i)
    {
        d += m_clients[i].receiver->dataPerSecond();
    }
    emit dataPerSecond(d, dataUp);
    dataUp = 0;
}

void VOIP::setPort(quint16 port, const QString& ip)
{
    if(port<1024)
        port=1024;

    if(ip.isEmpty())
    {
        m_port=port;
        for(int i=0;i<m_clients.size();++i)
            m_clients[i].receiver->setPort(port);
    }
    else
    {
        int in=indexOf(ip);
        if(in==-1)
            return;
        m_clients[in].receiver->setPort(port);
    }
}

int VOIP::indexOf(const QString& IP) const
{
    for(int i=0;i<m_clients.size();++i)
    {
        if(m_clients[i].IP==IP) return i;
    }
    return -1;
}

void VOIP::add(const QString& cl, quint16 port)
{
    if(contains(cl))
        remove(cl);

    if(port<1024)
        port=m_port;

    m_clients.append(VOIPClient(cl, port, new SoundReceiver(QHostAddress(cl), m_port, SAMPLE_RATE), new Sound(SAMPLE_RATE)));

    m_clients.last().sound->setVolume(m_volume);
}

void VOIP::removeAll()
{
    for(int i=0;i<m_clients.size();++i)
    {
        delete m_clients[i].sound;
        delete m_clients[i].receiver;
    }
    m_clients.clear();
}

bool VOIP::mute(const QString& cl)
{
    int index = indexOf(cl);
    if(index==-1)
        return true;

    m_clients[index].sound->mute();
    return false;
}

bool VOIP::unmute(const QString& cl)
{
    int index = indexOf(cl);
    if(index==-1)
        return true;

    m_clients[index].sound->unmute();
    return false;
}

bool VOIP::remove(const QString& cl)
{
    int index = indexOf(cl);
    if(index==-1)
        return true;
    delete m_clients[index].sound;
    delete m_clients[index].receiver;
    m_clients.removeAt(index);
    return false;
}
