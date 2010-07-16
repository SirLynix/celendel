#include "SoundManager.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDir>

Sound::Sound(const QByteArray& d, const QString& n)
{
    data=d;
    name=n;
    music=new sf::Music;
    if(!music->OpenFromMemory(data.constData(), data.size()))
    {
        delete music;
        music=NULL; //Be carefull not to try to play it !
        qDebug()<<"File \"" << n << "\" can't be loaded. ";
        data.clear();
    }
}

Sound::~Sound()
{
    delete music;
}

bool SoundLib::createSoundLib(const QString& name, const QString& folder, LVER ver)
{
    QDir dir(folder);
    if(!dir.exists())
    {
        qDebug() << "Error : folder \"" << folder << "\" not found.";
        return true;
    }
    QStringList filters;
    filters << "*.wav" << "*.ogg";
    dir.setNameFilters(filters);
    QStringList fileList = dir.entryList(QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks|QDir::Readable);

    for(int i=0;i<fileList.size();++i)
    {
        fileList[i]=folder+QDir::separator()+fileList[i];
    }
    return createSoundLib(name, fileList, ver);
}

bool SoundLib::createSoundLib(const QString& name, const QStringList& fileList, LVER ver)
{
    bool err=false;
    if(fileList.isEmpty())
    {
        qDebug() << "Error : no file to pack.";
        return true;
    }

    QFile f(LIB_FOLDER+name+LIB_EXT);
    if(!f.open(QIODevice::WriteOnly|QIODevice::Truncate))
        return true;

    QStringList fileName;

    for(int i=0;i<fileList.size();++i)
        fileName.append(fileList[i].mid(fileList[i].lastIndexOf(QDir::separator())+1));

    QDataStream in(&f);

    in<<(LVER)0;
    in<<fileName;
    for(int i=0; i<fileList.size();++i)
    {
        QFile t(fileList[i]);
        if(!t.open(QIODevice::ReadOnly))
        {
            err=true;
            qDebug() << "Error : file \"" << fileList[i] << "\" not found.";
        }
        else
        {
            qDebug() << "Processing file \"" << fileList[i] << " -> "<< fileName[i] << "\"...";
            in<<t.readAll();
        }
    }
    return err;
}

SoundLib::SoundLib(const QString& n, LVER ver)
{
    name=n;
    version=-1;
    m_error = false;

    QFile f(LIB_FOLDER+n+LIB_EXT);
    if(!f.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error : lib \"" << n << "\" not found.";
        m_error=true;
        return;
    }

    QDataStream in(&f);

    in>>version;
    in>>soundsName;

    if(ver!=-1)
    {
        if(ver>version)
        {
            qDebug() << "Warning : the local version (" << version << ") of \"" << n << "\"lib is older than the requested version (" << ver <<")";
        }
        else if(ver<version)
        {
            qDebug() << "Warning : the local version (" << version << ") of \"" << n << "\"lib is newer than the requested version (" << ver <<")";
        }
    }

    soundsName.removeAll("");

    if(soundsName.isEmpty())
    {
        qDebug() << "Error : sound list in \"" << n << "\" is empty.";
        m_error=true;
        return;
    }

    bool b=true;
    while(b)
    {
        for(int i=0; i<soundsName.size();++i)
        {
            if(soundsName.count(soundsName[i])>1)
            {
                QString n = soundsName[i];
                soundsName.removeAll(n);
                soundsName.append(n);
                break;
            }
            if(i+1==soundsName.size())
                b=false;
        }
    }


    for(int i=0; i<soundsName.size();++i)
    {
        QByteArray dta;
        in>>dta;
        sounds.append(new Sound(dta, soundsName[i]));
    }
}

SoundLib::~SoundLib()
{
    for(int i=0;i<sounds.size();++i)
        delete sounds[i];
}

SoundManager& SoundManager::getSoundManager()
{
    static SoundManager sndmngr;
    return sndmngr;
}

SoundManager::SoundManager() : m_volume(100)
{
}

QStringList SoundManager::getLibsSounds(RSID lib)
{
    if(lib<0||lib>m_libs.size())
        return QStringList();

    QStringList l;

    for(int i=0;i<m_libs[lib]->sounds.size();++i)
    {
        if(m_libs[lib]->sounds[i]->isValid())
            l.append(m_libs[lib]->sounds[i]->name);
    }

    return l;
}

QStringList SoundManager::getLibsSounds(const QString& lib)
{
    return getLibsSounds(libRSIDFromString(lib));
}

RSID SoundManager::libRSIDFromString(const QString& lib) const
{
    for(int i=0;i<m_libs.size();++i)
        if(m_libs[i]->name==lib)
            return i;

    return -1;
}

RSID SoundManager::soundRSIDFromString(RSID lib, const QString& sound) const
{
    if(lib==-1 || lib>=m_libs.size())
        return -1;

    for(int i=0;i<m_libs[lib]->sounds.size();++i)
        if(m_libs[lib]->sounds[i]->name==sound)
            return i;

    return -1;
}

RSID SoundManager::soundRSIDFromString(const QString& lib, const QString& sound) const
{
    return soundRSIDFromString(libRSIDFromString(lib), sound);
}

void SoundManager::setLibList(QStringList list, const QList<LVER>& ver)
{
    list.removeAll("");

    if(list.isEmpty())
    {
        clearCache();
        return;
    }

    bool b=true;
    while(b)
        for(int i=0; i<list.size();++i)
        {
            if(list.count(list[i])>1)
            {
                QString n = list[i];
                list.removeAll(n);
                list.append(n);
                break;
            }
            if(i+1==list.size())
                b=false;
        }
    buildCache(list, ver);
}

QStringList SoundManager::loadedLibs() const
{
    QStringList ret;
    for(int i=0; i<m_libs.size();++i)
    {
        if(!m_libs[i]->error())
            ret<<m_libs[i]->name;
    }
    return ret;
}

void SoundManager::setVolume(float volume)
{
    m_volume=volume;
    for(int j=0;j<m_libs.size();++j)
        for(int i=0;i<m_libs[j]->sounds.size();++i)
            if(m_libs[j]->sounds[i]->music!=NULL)
                m_libs[j]->sounds[i]->music->SetVolume(volume);
}

bool SoundManager::playSound(const QString& lib, RSID ID)
{
    return playSound(libRSIDFromString(lib), ID);
}

bool SoundManager::playSound(const QString& lib, const QString& sound)
{
    return playSound(libRSIDFromString(lib), soundRSIDFromString(lib, sound));
}

bool SoundManager::exists(const QString& lib, const QString& sound) const
{
    RSID lid = libRSIDFromString(lib);
    if(lid==-1)
        return false;
    RSID id = soundRSIDFromString(lid, sound);
    if(id==-1)
        return false;
    return m_libs[lid]->sounds[id]->isValid();
}

bool SoundManager::playSound(RSID lID, RSID ID)
{
    if(lID >= m_libs.size())
        return true;

    if(ID >= m_libs[lID]->sounds.size())
        return true;
    if(m_libs[lID]->sounds[ID]->music==NULL)
        return true;

    m_libs[lID]->sounds[ID]->music->Play();
    return false;
}

void SoundManager::stopSounds()
{
    for(int j=0;j<m_libs.size();++j)
        for(int i=0;i<m_libs[j]->sounds.size();++i)
            if(m_libs[j]->sounds[i]->music!=NULL)
                m_libs[j]->sounds[i]->music->Stop();
}

bool SoundManager::stopSound(const QString& lib, RSID ID)
{
    return stopSound(libRSIDFromString(lib), ID);
}

bool SoundManager::stopSound(RSID lID, RSID ID)
{
    if(lID<0||lID >= m_libs.size())
        return true;

    if(ID<0||ID >= m_libs[lID]->sounds.size())
        return true;
    if(m_libs[lID]->sounds[ID]->music==NULL)
        return true;

    m_libs[lID]->sounds[ID]->music->Stop();
    return false;
}

bool SoundManager::stopSound(const QString& lib, const QString& sound)
{
    RSID lid=libRSIDFromString(lib);
    return stopSound(lid, soundRSIDFromString(lid,sound));
}

void SoundManager::clearCache()
{
    for(int i=0; i<m_libs.size();++i)
        delete m_libs[i];
    m_libs.clear();
}

bool SoundManager::buildCache(const QStringList& libList, const QList<LVER>& versionLibList)
{
    bool er=false;
    bool v=true;
    if(versionLibList.size()!=libList.size())
        v=false;

    clearCache();
    for(int i=0;i<libList.size();++i)
    {
        LVER ver=-1;
        if(v)
            ver=versionLibList[i];

        m_libs.append(new SoundLib(libList[i], ver));
    }
    return er;
}

SoundManager::~SoundManager()
{
    clearCache();
}
