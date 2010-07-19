#ifndef OPENAL_H
#define OPENAL_H
#include "global.h"
#include <OpenAL/alc.h>

class OpenAL
{
public:
    OpenAL();
    ~OpenAL();

    bool hasCapture();

private:
    ALCdevice * m_device;
    ALCcontext * m_context;
};

#endif // OPENAL_H
