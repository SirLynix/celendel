#include "Packet.h"
#include <QtNetwork>
#include <QDateTime>

#include <QDebug>
void Packet::show() const //Temporary - only for debug and tests
{
    qDebug() << "ID=" + QString::number(ID) + "\nType=" + QString::number(type) + "\nDataSize=" + QString::number(dataSize) + "\ntimestamp=" + QString::number(timestamp) + "\nDatas=\n" << data;
}

Packet::Packet() : ID(0), type(0), dataSize(0), timestamp(-1)
{
    static qint32 sID = 0;
    ID=sID;
    ++sID;
    full=false;
}

void Packet::setHeader(QDataStream& in)
{
    in>>ID>>type>>dataSize>>timestamp;
}


void Packet::unSerialise(QByteArray& pa)
{
    QDataStream in(pa);
    setHeader(in);
    setBody(in);
}

void Packet::serialise(QByteArray& pa)
{
    if(timestamp==-1)
    {
        timestamp=QDateTime::currentDateTime().toTime_t()*1000+QTime::currentTime().msec();
    }


    QDataStream out(&pa, QIODevice::WriteOnly);

    out << (qint32)ID;
    out << (qint32)type;
    out << (qint32)0;
    out << (qint32)timestamp;
    out << data;
    out.device()->seek(2*sizeof(qint32));
    dataSize=pa.size()-sizeofheader;
    out << (quint32)dataSize;

}

void Packet::setBody(QDataStream& in)
{
    in>>data;
    full=true;
}
