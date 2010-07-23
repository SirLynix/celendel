#ifndef DEF_VOIP
#define DEF_VOIP

#include <QThread>
#include "SoundReceiver.h"
#include "Sound.h"
#include "Recorder.h"
#include "Speex.h"
#include "Global.h"

#define VOIP_PORT 5566
#define SAMPLE_RATE 8000


class VOIP : public QObject
{
    Q_OBJECT
    public:
        VOIP(QObject* p=NULL);
        void add(const QString& cl);
        void removeAll();
        bool remove(const QString& cl);

        bool mute(const QString& cl);
        bool unmute(const QString& cl);

        float quality() const { return speex.quality(); }
        bool isEnabled() const { return m_enabled; }

        ~VOIP();

    public slots:
        void setQuality(float q);
        void setVolume(float volume);
        void setEnabled(bool);

    private slots:
        void update();
        void send(QByteArray b);

    signals:
        void dataPerSecond(int, int);

    private:
        VOIPSystem::Speex speex;
        QUdpSocket* udpSocket;
        QStringList m_clients;
        QList<VOIPSystem::SoundReceiver*> m_receivers;
        QList<VOIPSystem::Sound*> m_sounds;
        VOIPSystem::Recorder *rec;
        int dataUp;

        float m_volume;
        bool m_enabled;

        int m_floor;

};
/*
VOIP& getVOIP();*/

class VOIPThread : public QThread //Multi-thread interface
{
    Q_OBJECT
    public:
        VOIPThread(QObject* p=NULL);
        ~VOIPThread();

        bool remove(const QString& cl) {mutex.lock(); bool e=m_voip->remove(cl);mutex.unlock();return e;}

        bool mute(const QString& cl) {mutex.lock(); bool e=m_voip->mute(cl);mutex.unlock();return e;}
        bool unmute(const QString& cl) {mutex.lock(); bool e=m_voip->unmute(cl);mutex.unlock();return e;}

        float quality() { mutex.lock();float q=m_voip->quality();mutex.unlock();return q; }
        bool isEnabled() { mutex.lock(); bool e=m_voip->isEnabled(); mutex.unlock(); return e; }

    public slots:
        void setQuality(float q) {mutex.lock(); m_voip->setQuality(q); mutex.unlock();}
        void setVolume(float volume) {mutex.lock(); m_voip->setVolume(volume); mutex.unlock();}
        void setEnabled(bool b) {mutex.lock(); m_voip->setEnabled(b); mutex.unlock();}
        void add(const QString& cl) {mutex.lock(); m_voip->add(cl); mutex.unlock();}
        void removeAll() {mutex.lock(); m_voip->removeAll(); mutex.unlock();}

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
