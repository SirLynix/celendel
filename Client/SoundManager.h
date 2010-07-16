#ifndef DEF_SOUNDMANAGER
#define DEF_SOUNDMANAGER

#include "..\Shared\Constants.h"
#include <QStringList>
#include <QObject>
#include "SFML\Audio.hpp"

#define LIB_FOLDER "Sounds/"
#define LIB_EXT ".soundlib"

struct Sound
{
    Sound(const QByteArray& d, const QString& n);
    ~Sound();

    QByteArray data;
    QString name;
    sf::Music* music;

    bool isValid() const { return music!=NULL; }

    private:
    Sound(const Sound&);
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

    static bool createSoundLib(const QString& name, const QStringList& fileList, LVER ver=0);
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

        void setLibList(QStringList list, const QList<LVER>& ver=QList<LVER>());

        void setVolume(float volume);

        QStringList loadedLibs() const;

        QStringList getLibsSounds(RSID lib);
        QStringList getLibsSounds(const QString& lib);

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

        bool buildCache(const QStringList& libList, const QList<LVER>& versionLibList=QList<LVER>());
        void clearCache();

        float m_volume;
        QList<SoundLib*> m_libs;
        SoundManager(const SoundManager&); ///Uncopiable
        SoundManager(); ///The user has to use the getSoundManager() func
};

#define sndMngr SoundManager::getSoundManager()

#endif
