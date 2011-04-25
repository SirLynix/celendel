#ifndef DEF_SOUNDMANAGER
#define DEF_SOUNDMANAGER

#include "../Shared/Constants.h"
#include <QStringList>
#include <QDir>
#include "SFML\Audio.hpp"

#define LIB_FOLDER "Sounds/"
#define TMP_FOLDER QDir::tempPath()+"/Celendel/SoundCache/"
#define LIB_EXT ".soundlib"
#define RAM_CACHE_LIMIT 1024*64 //64ko

#define LR(a) (a>=0&&a<m_libs.size())
#define SR(l,a) (a>=0&&LR(l)&&a<m_libs[l]->sounds.size())

struct Sound
{
    Sound(const QByteArray& d, const QString& n);
    ~Sound();

    QByteArray data;
    QString name;
    sf::Music* music;

    bool isValid() const { return music!=NULL; }

    bool isFileCached() const { return m_fileCached; }

    private:
    Sound(const Sound&);
    bool m_fileCached;
};

struct SoundLib
{
    SoundLib(const QString& n, LVER ver=-1);
    ~SoundLib();

    QString name;
    LVER version;
    QStringList soundsName;
    QList<Sound*> sounds;

    bool error() const {return m_error;}

    QStringList getSoundList() const;

    static bool createSoundLib(const QString& name, const QStringList& fileList, LVER ver=0, const QString& folder = "");
    static bool createSoundLib(const QString& name, const QString& folder, LVER ver=0);

    private:
    SoundLib(const SoundLib&);
    bool m_error;
};

class SoundManager : public QObject
{
    Q_OBJECT
    public:
        static SoundManager& getSoundManager();
        ~SoundManager();

        void setLibList(QStringList list);
        void setLibList(const QList<SoundLibInformations>& list);

        void setVolume(float volume);

        QStringList loadedLibs() const;

        QStringList getLibsSounds(RSID lib);
        QStringList getLibsSounds(const QString& lib);

        QList<SoundLibInformations> getLibsInfo() const;
        SoundLibInformations getLibInfo(const QString& lib) const;
        SoundLibInformations getLibInfo(RSID lib) const;

        bool isLibLoaded(RSID id) const { if(!LR(id)) return false; return !m_libs[id]->error(); }
        bool isLibLoaded(const QString& lib) const { return isLibLoaded(libRSIDFromString(lib)); }

        RSID libRSIDFromString(const QString& lib) const;
        RSID soundRSIDFromString(RSID lib, const QString& sound) const;
        RSID soundRSIDFromString(const QString& lib, const QString& sound) const;

        bool playSound(RSID lib, RSID ID);
        bool playSound(const QString& lib, RSID ID);
        bool playSound(const QString& lib, const QString& sound);
        void stopSounds();
        bool stopSound(RSID lib, RSID ID);
        bool stopSound(const QString& lib, RSID ID);
        bool stopSound(const QString& lib, const QString& sound);

        bool exists(const QString& lib, const QString& sound="") const;

    private:

        bool buildCache(const QList<SoundLibInformations>&);
        void clearCache();

        float m_volume;
        QList<SoundLib*> m_libs;
        SoundManager(const SoundManager&); ///Uncopiable
        SoundManager(); ///The user has to use the getSoundManager() func
};

#define sndMngr SoundManager::getSoundManager()

#endif
