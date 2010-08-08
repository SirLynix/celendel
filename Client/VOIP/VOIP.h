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

};

class VOIPThread : public QThread //Multi-thread interface
{
    Q_OBJECT
    public:
        VOIPThread(QObject* p=NULL);
        ~VOIPThread();

        bool remove(const QString& cl) {mutex.lock(); bool e=m_voip->remove(cl);mutex.unlock();return e;}

        bool mute(const QString& cl) {mutex.lock(); bool e=m_voip->mute(cl);mutex.unlock();return e;}
        bool unmute(const QString& cl) {mutex.lock(); bool e=m_voip->unmute(cl);mutex.unlock();return e;}

        float quality() { mutex.lock();float q=m_voip->quality();mutex.unlock();return q;}
        bool isEnabled() { mutex.lock(); bool e=m_voip->isEnabled(); mutex.unlock();return e;}

        bool contains(const QString& IP) {mutex.lock();bool e=m_voip->contains(IP);mutex.unlock();return e;}

        float volume(const QString& ip="") {mutex.lock();float e=m_voip->volume(ip);mutex.unlock();return e;}

        bool changeCaptureDevice(const QString& name) {mutex.lock();bool e=m_voip->changeCaptureDevice(name);mutex.unlock();return e;}

    public slots:
        void setQuality(float q) {mutex.lock(); m_voip->setQuality(q); mutex.unlock();}
        void setVolume(float volume, const QString& ip="") {mutex.lock(); m_voip->setVolume(volume,ip); mutex.unlock();}
        void setEnabled(bool b) {mutex.lock(); m_voip->setEnabled(b); mutex.unlock();}
        void add(const QString& cl) {mutex.lock(); m_voip->add(cl); mutex.unlock();}
        void removeAll() {mutex.lock(); m_voip->removeAll(); mutex.unlock();}

        void setPort(quint16 port, const QString& ip="") {mutex.lock(); m_voip->setPort(port,ip); mutex.unlock();}

    private slots:
        void dtaPS(int d, int u) { emit dataPerSecond(d,u);}

    signals:
        void dataPerSecond(int, int);

    protected:
        void run();
    private:
        VOIP* m_voip;
        QThread* t;
        QMutex mutex;
};

VOIPThread& getVOIP();

#endif
