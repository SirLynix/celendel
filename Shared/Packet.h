#ifndef PACKET_H
#define PACKET_H

#include <QObject>

#define sizeofheader 4*sizeof(qint32)

class Packet : public QObject
{
    public:
        Packet();
        void setHeader(QDataStream& in);
        void setBody(QDataStream& in);

        void unSerialise(QByteArray& pa);
        void serialise(QByteArray& pa);

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
        Packet(const Packet&) {} ///Non-copiable
};

#endif // PACKET_H
