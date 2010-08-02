#ifndef DEF_SOUNDRECEIVER
#define DEF_SOUNDRECEIVER

#include <QObject>
#include "global.h"
#include "Speex.h"
#include <QtNetwork>

namespace VOIPSystem
{

class SoundReceiver : public QObject
{
    Q_OBJECT
    public:
        SoundReceiver(const QHostAddress& hostAddress, const quint16& port, int sampleRate);
        int dataPerSecond();

    public slots:
        void setPort(quint16 port);

    private slots:
        void readPendingDatagrams();
        void decoded(const ALshortVector& samples);
        void update();

    signals:
        void dataReceived(const ALshortVector& samples);

    private:
        Speex speex;
        int dta;
        int DPS;
        QUdpSocket *udpSocket;
        QHostAddress m_IP;
};
}

#endif // DEF_SOUNDRECEIVER
