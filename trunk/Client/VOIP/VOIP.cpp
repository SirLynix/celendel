#include "VOIP.h"

#include <QDebug>

#define D() qDebug() << __FILE__ << ";" << __LINE__

QStringList getOALDevices(bool output)
{
    if(alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT")==AL_FALSE)
        return QStringList();

    QStringList list;
    ALenum p=ALC_DEVICE_SPECIFIER;
    if(!output)
        p=ALC_CAPTURE_DEVICE_SPECIFIER;

    const ALCchar *str=alcGetString(NULL, p);

    int size=0;
    for(;str[size]!='\0'&&str[size+1]!='\0';++size);
    size+=2;



    int c=0;
    for(int i=0; i<size;++i)
    {
        if(str[i]=='\0')
        {
            QString s; s.resize(i-c);
            for(int j=c; j<i; ++j)
            {
                s[j-c]=str[j];
            }
            list<<s;
            c=i+1;
        }
    }

    return list;
}

QString getOALCurrentDevice(bool output)
{
    ALCcontext *ctxt=alcGetCurrentContext();
    if(ctxt==NULL)
        return QString();

    ALCdevice *cdvc = alcGetContextsDevice(ctxt);
    if(cdvc==NULL)
        return QString();

    ALenum p=ALC_DEVICE_SPECIFIER;
    if(!output)
        p=ALC_CAPTURE_DEVICE_SPECIFIER;

    const ALCchar *a = alcGetString(cdvc, p);
    int size=0;
    for(;a[size]!='\0';++size);
    QString s; s.resize(size);
    for(int i=0;i<size;++i)
    {
        s[i]=a[i];
    }
    return s;
}

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

    QTimer* updateT = new QTimer;
    connect(updateT, SIGNAL(timeout()), this, SLOT(update()));
    updateT->start(1000);

    udpSocket = new QUdpSocket(this);
    m_port=VOIP_DEFAULT_PORT;

    m_receiver=0;
    m_sound=new Sound(SAMPLE_RATE);
    m_sound->play();

    dataUp = 0;
    setVolume(50);
    m_enabled=true;
    setQuality(4);

    updateT->moveToThread(&m_thread);
    moveToThread(&m_thread);
    m_thread.start();
}

VOIP::~VOIP()
{
    disconnect();
}

void VOIP::connectToServer(const QString& IP, quint16 port)
{
    if(port<1024) port=1024;

    if(!m_IP.isEmpty())
        disconnect();

    m_port=port; m_IP=IP;

    m_receiver=new SoundReceiver(QHostAddress(m_IP), m_port, SAMPLE_RATE);

    connect(m_receiver, SIGNAL(dataReceived(const ALshortVector&)), m_sound, SLOT(queue(const ALshortVector&)));
}

void VOIP::disconnect()
{
    m_IP="";
    delete m_receiver; m_receiver=0;
}

float VOIP::volume() const
{
    return m_volume;
}

void VOIP::setVolume(float vol)
{
    if(vol<0)
    {
        vol=0;
    }
    else if(vol>100)
    {
        vol=1;
    }
    else
        vol=vol/100;

    m_volume=vol;

    m_sound->setVolume(vol);
}

void VOIP::setEnabled(bool e)
{
    m_enabled=e;

    if(!m_enabled)
        m_sound->mute();
    else
        m_sound->unmute();
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
    if(m_IP.isEmpty())
        return;

  //  D();

    if(b.size() > m_floor && m_enabled)
    {
        qDebug() << m_IP;
        udpSocket->writeDatagram(b, QHostAddress(m_IP), m_port);
        dataUp += b.size();
    }
}

void VOIP::update()
{
    int d=0;
    if(m_receiver)
        d=m_receiver->dataPerSecond();

    emit dataPerSecond(d, dataUp);
    dataUp = 0;
}
