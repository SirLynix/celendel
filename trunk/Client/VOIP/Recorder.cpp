#include "Recorder.h"
#include <QDebug>
#include <QTimer>

namespace VOIPSystem
{

Recorder::Recorder(size_t _sampleRate, QObject *p)
        : QObject(p)
        , m_sampleRate(_sampleRate)
        , m_frameSize(m_sampleRate * 20 / 1000)
        , m_timer(new QTimer(this))
        , m_record(false)
        , m_captureDevice(alcCaptureOpenDevice(0, m_sampleRate, AL_FORMAT_MONO16, m_sampleRate))
        , m_error(m_captureDevice == 0)
{
    m_timer->setInterval(20);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(capture()));
}

void Recorder::startRecord()
{
    if (!m_timer->isActive())
    {
        alcCaptureStart(m_captureDevice);
        m_timer->start();
    }
}

int Recorder::sampleRate() const
{
    return m_sampleRate;
}

int Recorder::sampleAvailable()
{
    ALCint SamplesAvailable = 0;
    alcGetIntegerv(m_captureDevice, ALC_CAPTURE_SAMPLES, 1, &SamplesAvailable);
    return SamplesAvailable;
}

QVector<ALshort> Recorder::readSamples(int nbSamples)
{
    m_samples.resize(nbSamples);
    alcCaptureSamples(m_captureDevice, &m_samples[0], nbSamples);

    return m_samples;
}

void Recorder::capture()
{
    int samples = sampleAvailable();
    while(samples >= m_frameSize)
    {
        emit readyRead(readSamples(m_frameSize));
        samples -= m_frameSize;
    }
}

void Recorder::stopRecord()
{
    alcCaptureStop(m_captureDevice);
    m_timer->stop();
}

bool Recorder::error()
{
    return m_error;
}

Recorder::~Recorder()
{
    stopRecord();
    alcCaptureCloseDevice(m_captureDevice);
}

void Recorder::setFrameSize(int frameSize)
{
    qDebug("frame size: %d", frameSize);
    m_frameSize = frameSize;
    m_samples.resize(m_frameSize);
}

}
