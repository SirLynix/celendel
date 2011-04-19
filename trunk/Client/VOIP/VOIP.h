#ifndef DEF_VOIP
#define DEF_VOIP

#include <QThread>
#include <QStringList>
#include "SoundReceiver.h"
#include "Sound.h"
#include "Recorder.h"
#include "Speex.h"
#include "Global.h"

#define VOIP_DEFAULT_PORT 5566
#define SAMPLE_RATE 8000

QStringList getOALDevices(bool output=true); //If true, list the output devices. If false, list the capture devices.
QString getOALCurrentDevice(bool output=true); //Same

struct VOIPClient
{
    VOIPClient(const QString& ip, quint16 p, VOIPSystem::SoundReceiver* rec, VOIPSystem::Sound* so):IP(ip),port(p),receiver(rec),sound(so)
    {
        QObject::connect(receiver, SIGNAL(dataReceived(const ALshortVector&)), sound, SLOT(queue(const ALshortVector&)));
        sound->play();
    }
    QString IP;
    quint16 port;
    VOIPSystem::SoundReceiver* receiver;
    VOIPSystem::Sound* sound;
};

class Thread : public QThread
{
    public:
    Thread(QObject* p=0):QThread(p) {}
    protected:
    void run() { exec(); }
};

class VOIP : public QObject
{
    Q_OBJECT
    public:
        VOIP(QObject* p=NULL);
        ~VOIP();

        void add(const QString& cl, quint16 port=0);
        void removeAll();
        bool remove(const QString& cl);

        bool mute(const QString& cl);
        bool unmute(const QString& cl);
        bool muted(const QString& IP) const{ int in=indexOf(IP); if(in==-1) return false; return m_clients[in].sound;}

        float quality() const { return speex.quality(); }
        float volume(const QString& ip="") const;
        bool isEnabled() const { return m_enabled; }

        bool changeCaptureDevice(const QString& name) { return rec->changeDevice(name); }


        bool contains(const QString& IP) const { return indexOf(IP)!=-1; }

    public slots:
        void setQuality(float q);
        void setVolume(float volume, const QString& ip="");
        void setEnabled(bool);

        void setPort(quint16 port, const QString& ip="");

    private slots:
        void update();
        void send(QByteArray b);

    signals:
        void dataPerSecond(int, int);

    private:
        int indexOf(const QString& IP) const;
        VOIPSystem::Speex speex;
        QUdpSocket* udpSocket;
        QList<VOIPClient> m_clients;
        VOIPSystem::Recorder *rec;
        int dataUp;

        float m_volume;
        bool m_enabled;

        int m_floor;
        quint16 m_port;

        Thread m_thread;

};

VOIP& getVOIP();
#endif
