#include "SoundLibThread.h"
#include "SoundManager.h"

SoundLibThread::SoundLibThread(const QString& name, const QString& folder):m_name(name),m_folder(folder)
{
    start();
}

void SoundLibThread::run()
{
    SoundLib::createSoundLib(m_name, m_folder);
}
