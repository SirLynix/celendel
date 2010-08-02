#include "Sound.h"
#include <QTimer>
#include <QDebug>

namespace VOIPSystem
{

Sound::Sound(ALsizei sampleRate)
        : m_sampleRate(sampleRate)
        , m_volume(1.0f)
        , m_paused(false)
        , m_playing(false)
        , m_source(0)
        , m_timer(new QTimer(this))
        , m_freeze(false)
{
    m_timer->setInterval(20);
    alGenSources(1, &m_source);
    setVolume(m_volume);
    allocateBuffers(100); //100 frames of 20ms each in this case, (2 secs).

    m_muted=false;

    connect(m_timer, SIGNAL(timeout()), this, SLOT(testPlaying()));
}


void Sound::allocateBuffers(int nb)
{
    for(int i = 0; i < nb; ++i)
    {
        ALuint buf;
        alGenBuffers(1, &buf);
        m_freeBuffers.enqueue(buf);
    }
}
void Sound::stop()
{
    alSourceStop(m_source);
    m_timer->stop();
}

void Sound::pause()
{
    alSourcePause(m_source);
    m_timer->stop();
    m_paused = true;
}

void Sound::setVolume(const ALfloat& v)
{
    m_volume = v;
    if(!m_muted)
        alSourcef(m_source, AL_GAIN, v);
}

void Sound::mute()
{
    m_muted=true;
    alSourcef(m_source, AL_GAIN, 0.0f);
}

void Sound::unmute()
{
    m_muted=false;
    alSourcef(m_source, AL_GAIN, m_volume);
}

void Sound::play()
{
    m_paused = false;
    m_playing = true;
    if(state() != AL_PLAYING)
    {
        alSourcePlay(m_source);
        m_timer->start();
    }
}

int Sound::getQueuedBuffers()
{
    ALint nb = 0;
    alGetSourcei(m_source, AL_BUFFERS_QUEUED, &nb);
    return nb;
}

void Sound::testPlaying()
{
    cleanBuffers();

    if(state() != AL_PLAYING && !m_paused && m_playing && getQueuedBuffers())
    {
        alSourcePlay(m_source);
    }
}

ALint Sound::state()
{
    ALint Status = 0;
    alGetSourcei(m_source, AL_SOURCE_STATE, &Status);
    return Status;
}

void Sound::cleanBuffers()
{
    ALint v = 0;
    alGetSourcei(m_source, AL_BUFFERS_PROCESSED, &v);
    for(; v; --v)
    {
        ALuint b;
        alSourceUnqueueBuffers(m_source, 1, &b);
        m_freeBuffers.enqueue(b);
    }
}

void Sound::queue(const ALshortVector & samples)
{
    static int count = m_freeBuffers.size();

    if(m_freeze) // If the sound buffer is full, adding more is useless, and would only inflate the lag.
    {
        if(m_freeBuffers.size() < count)
            return;

        qDebug("Buffer empty, unfreezing.");
        m_freeze = false;
    }
    ALuint Buffer;
    if (m_freeBuffers.isEmpty())
    {
        qDebug("Buffer full ! No more frame allowed until it's empty");
        m_freeze = true;
        return;
    }
    Buffer = m_freeBuffers.dequeue();


    alBufferData(Buffer, AL_FORMAT_MONO16, samples.data(), samples.size() * sizeof(ALushort), m_sampleRate);
    alSourceQueueBuffers(m_source, 1, &Buffer);
}

Sound::~Sound()
{
    stop();
    alDeleteSources(1, &m_source);
    foreach(ALuint buf, m_freeBuffers)
    {
        alDeleteBuffers(1, &buf);
    }
}

}
