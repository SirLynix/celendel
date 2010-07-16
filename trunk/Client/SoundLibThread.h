#ifndef DEF_SOUNDLIBTHREAD
#define DEF_SOUNDLIBTHREAD

#include <QThread>


class SoundLibThread : public QThread
{
    Q_OBJECT
    public:
        SoundLibThread(const QString& name, const QString& folder);
    protected:
        void run();

    private:
        QString m_name;
        QString m_folder;
};

#endif // DEF_SOUNDLIBTHREAD
