#ifndef DEF_VOIP
#define DEF_VOIP

#include <QObject>
#include "SoundReceiver.h"
#include "Sound.h"
#include "Recorder.h"
#include "Speex.h"
#include "Global.h"

#define PORT 7755
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

VOIP& getVOIP();

#endif
