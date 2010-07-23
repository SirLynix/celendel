#include "SoundLibThread.h"
#include "SoundManager.h"

SoundLibThread::SoundLibThread(const QString& name, const QString& folder):m_name(name),m_folder(folder)
{
    m_error=false;
    m_mode=DIRECTORY;
    start();
}

SoundLibThread::SoundLibThread(const QString& name, const QStringList& list):m_name(name),m_list(list)
{
    m_error=false;
    m_mode=FILE_LIST;
    start();
}

void SoundLibThread::run()
{
    if(m_mode==DIRECTORY)
    {
        m_error=SoundLib::createSoundLib(m_name, m_folder);
    }
    else if(m_mode==FILE_LIST)
    {
        m_error=SoundLib::createSoundLib(m_name, m_list);
    }
    else
    {
        m_error=true;
    }
}
