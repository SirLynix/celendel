#include "Packet.h"
#include <QtNetwork>
#include <QDateTime>

#include <QDebug>

#define VD(a) if(a.status()!=QDataStream::Ok) {qDebug() << "Packet error : " << __FILE__ << ":" << __LINE__; setError();}
#define RVD(a) VD(a); return m_error;
#define MAGIC_NUMBER static_cast<qint32>(0x1337C0D3)

quint32 getTimeStamp(){return QDateTime::currentDateTime().toTime_t()*1000+QTime::currentTime().msec();}

Packet::Packet() : ID(0), type(0), dataSize(0), timestamp(-1)
{
    static qint32 sID = 0;
    ID=sID;
    ++sID;
    full=false;
    m_error=false;
}

bool Packet::setHeader(QDataStream& in)
{
    qint32 magic;
    in>>magic;

    if(magic!=MAGIC_NUMBER||in.status()!=QDataStream::Ok)
    {
        qDebug() << "Wrong format !";
        setError();
        return true;
    }


    in>>ID>>type>>dataSize>>timestamp;
    RVD(in);
}

bool Packet::setBody(QDataStream& in)
{
    in>>data;
    full=true;
    RVD(in);
}

void Packet::setError()
{
    m_error=true;
    full=false;
    data=QByteArray();
    ID=-1;
    type=-1;
    dataSize=data.size();
    timestamp=-1;
}

bool Packet::unSerialise(QByteArray& pa)
{
    QDataStream in(pa);

    return setHeader(in)||setBody(in);
}

void Packet::serialise(QByteArray& pa)
{
    if(timestamp==-1)
    {
        timestamp=getTimeStamp();
    }


    QDataStream out(&pa, QIODevice::WriteOnly);

    out << MAGIC_NUMBER;
    out << static_cast<qint32>(ID);
    out << static_cast<qint32>(type);
    out << static_cast<qint32>(0);
    out << static_cast<qint32>(timestamp);
    out << data;
    out.device()->seek(3*sizeof(qint32));
    dataSize=pa.size()-sizeofheader;
    out << static_cast<qint32>(dataSize);

}
