#include "Speex.h"
namespace VOIPSystem
{

Speex::Speex(int sampleRate)
        : m_sampleRate(sampleRate)
        , m_frameSize(0)
{
    speex_bits_init(&ebits);
    enc_state = speex_encoder_init(&speex_nb_mode);
    setQuality(5);
    speex_encoder_ctl(enc_state,SPEEX_SET_SAMPLING_RATE,&m_sampleRate);
    int t = 1;
    speex_encoder_ctl(enc_state, SPEEX_SET_VBR, &t);
    speex_encoder_ctl(enc_state, SPEEX_SET_DTX, &t);
    speex_bits_init(&dbits);
    dec_state = speex_decoder_init(&speex_nb_mode);

    speex_decoder_ctl(dec_state, SPEEX_GET_FRAME_SIZE, &m_frameSize);

    m_buffer.resize(m_frameSize * 2);
    m_samples.resize(m_frameSize);
    preprocess_state = speex_preprocess_state_init(m_frameSize, m_sampleRate);
    speex_preprocess_ctl(preprocess_state, SPEEX_PREPROCESS_SET_VAD, &t);
    speex_preprocess_ctl(preprocess_state, SPEEX_PREPROCESS_SET_AGC, &t);
}

void Speex::encode(ALshortVector samples)
{
    speex_bits_reset(&ebits);

    speex_preprocess_run(preprocess_state, samples.begin());

    speex_encode_int(enc_state, samples.begin(), &ebits);
    int size = speex_bits_write(&ebits, m_buffer.data(), m_buffer.size());
    emit encoded(QByteArray(m_buffer,size));
}

void Speex::decode(QByteArray data)
{
    speex_bits_read_from(&dbits, data.data(), data.size());
    speex_decode_int(dec_state, &dbits, m_samples.begin());
    emit decoded(m_samples);
}

void Speex::setQuality(int q)
{
    if(q < 0)
        q = 0;
    if(q > 10)
        q = 10;
    m_quality = q;
    speex_encoder_ctl(enc_state,SPEEX_SET_QUALITY, &m_quality);
}

Speex::~Speex()
{
    speex_bits_destroy(&dbits);
    speex_decoder_destroy(dec_state);
    speex_bits_destroy(&ebits);
    speex_encoder_destroy(enc_state);
}
}
