#include "openal.h"

OpenAL::OpenAL()
        : m_device(alcOpenDevice(0))
        , m_context(alcCreateContext(m_device,0))
{
    alcMakeContextCurrent(m_context);
    qRegisterMetaType<ALshortVector >();
}

OpenAL::~OpenAL()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}

bool OpenAL::hasCapture()
{
    return alcIsExtensionPresent(m_device, "ALC_EXT_CAPTURE") == AL_TRUE;
}
