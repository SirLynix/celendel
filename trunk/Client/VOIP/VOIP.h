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

        void connectToServer(const QString& IP, quint16 port=0);
        void disconnect();


        float quality() const { return speex.quality(); }
        float volume() const;
        bool isEnabled() const { return m_enabled; }

        bool changeCaptureDevice(const QString& name) { return rec->changeDevice(name); }


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

        VOIPSystem::SoundReceiver* m_receiver;
        VOIPSystem::Sound* m_sound;

        VOIPSystem::Recorder *rec;
        int dataUp;

        float m_volume;
        bool m_enabled;

        int m_floor;

        quint16 m_port;
        QString m_IP;

        Thread m_thread;

};

VOIP& getVOIP();
#endif
