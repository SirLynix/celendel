#ifndef DEF_SOUNDLIBTHREAD
#define DEF_SOUNDLIBTHREAD

#include <QStringList>
#include <QThread>

enum LOADING_MODE {DIRECTORY, FILE_LIST};

class SoundLibThread : public QThread
{
    Q_OBJECT
    public:
        SoundLibThread(const QString& name, const QString& folder);
        SoundLibThread(const QString& name, const QStringList& list);

        bool error() const { return m_error;}

    protected:
        void run();

    private:
        QString m_name;
        QString m_folder;
        QStringList m_list;
        LOADING_MODE m_mode;
        bool m_error;
};

#endif // DEF_SOUNDLIBTHREAD
