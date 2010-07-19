#ifndef DEF_SPEEX
#define DEF_SPEEX

#include <QByteArray>
#include <speex/speex.h>
#include <speex/speex_preprocess.h>

#include "global.h"

namespace VOIPSystem
{

class Speex : public QObject
{
    Q_OBJECT
public:
    Speex(int sampleRate);
    ~Speex();
    int frameSize() const { return m_frameSize; }
    int quality() const { return m_quality; }

public slots:
    void setQuality(int q);
    void encode(ALshortVector samples);
    void decode(QByteArray data);

signals:
    void encoded(const QByteArray &);
    void decoded(const ALshortVector &);

private:
    int m_sampleRate;
    int m_quality;
    int m_frameSize;
    QByteArray m_buffer;
    ALshortVector m_samples;

    SpeexBits ebits;
    void *enc_state;
    SpeexBits dbits;
    void *dec_state;

    SpeexPreprocessState *preprocess_state;


};
}

#endif
