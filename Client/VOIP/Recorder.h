#ifndef DEF_RECORDER
#define DEF_RECORDER
#include "Global.h"
#include <QVector>

class QTimer;

namespace VOIPSystem
{

class Recorder : public QObject
{
    Q_OBJECT
    public:
        Recorder(size_t sampleRate, QObject* parent = 0);
        ~Recorder();
        bool error();
        int sampleRate() const;

    signals:
        void readyRead(ALshortVector);

    public slots:
        void startRecord();
        void stopRecord();
        void setFrameSize(int frameSize);

    private slots:
        void capture();


    private:
        int sampleAvailable();
        QVector<ALshort> readSamples(int nbSamples);

    private:
        int         m_sampleRate;
        int         m_frameSize;
        QTimer      *m_timer;
        bool        m_record;
        ALCdevice   *m_captureDevice;
        bool        m_error;

        QVector<ALshort> m_samples;
};

}

#endif
