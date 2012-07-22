#ifndef DEF_VOIPSERVER
#define DEF_VOIPSERVER

#include <QtNetwork>
#include <QStringList>
#include <QMap>


#define VOIP_DEFAULT_PORT 5566


class VOIPServer: public QObject
{
    Q_OBJECT

    public:
        VOIPServer(QObject *par=0, quint16 port=VOIP_DEFAULT_PORT);

        void  addTarget(const QString& IP, quint16 port=VOIP_DEFAULT_PORT);
        void  rmTarget(const QString& IP);

        void  addBlacklist(const QString& toBL, const QString& who);
        void  rmBlacklist(const QString& toBL, const QString& who);

    private slots:
        void readPendingDatagrams();

        void updateStats();

    signals:
        void statsUpdated(unsigned int down, unsigned int up);

    private:
        void resend(const QString& from, QByteArray& datagram);

        unsigned int m_dataDown;
        unsigned int m_dataUp;

        QUdpSocket* m_udpSocket;

        QMap<QString, quint16> m_tgList;

        QMap<QString, QStringList> m_blackList;

};

#endif
