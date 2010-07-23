#ifndef PACKET_H
#define PACKET_H

#include <QObject>

#define sizeofheader 5*sizeof(qint32)

quint32 getTimeStamp();

class Packet : public QObject
{
    public:
        Packet();

        bool setHeader(QDataStream& in); //Returns true on error, and set the error flag
        bool setBody(QDataStream& in); //Idem

        bool unSerialise(QByteArray& pa); //Idem
        void serialise(QByteArray& pa);

        bool error() const { return m_error;}

        ///Header
        qint32 ID;
        qint32 type;
        qint32 dataSize;
        qint32 timestamp;

        ///Body
        QByteArray data;

        ///Flag
        bool full;

        void show() const;

    private:
        void setError();
        Packet(const Packet&) {} ///Non-copiable
        bool m_error;
};

#endif // PACKET_H
