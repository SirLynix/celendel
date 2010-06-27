#include "Serializer.h"
#include <QDataStream>
#include <QDebug>
#include <ctime>
#include <cstdio>

int alea(int min,int max){static bool first=true;if(first){srand(time(NULL));first=false;alea(0,150);}return (int)(min+((float)rand()/RAND_MAX*(max-min+1)));}

void extractChatData(QByteArray& data, ENUM_TYPE& canal, QString& text)
{
    QDataStream in(data);

    in>>canal;
    in>>text;
}

QByteArray serialiseChatData(ENUM_TYPE canal, const QString& text)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(ENUM_TYPE)canal;
    out<<text;
    return data;
}

void extractErrorData(QByteArray& data, ENUM_TYPE& error_type, QString& text)
{
    QDataStream in(data);

    in>>error_type;
    in>>text;
}

QByteArray serialiseErrorData(ENUM_TYPE error_type, const QString& text)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(ENUM_TYPE)error_type;
    out<<text;

    return data;
}

void extractGMElectData(QByteArray& data, CLID& ID)
{
    QDataStream in(data);

    in>>ID;
}

QByteArray serialiseGMElectData(CLID ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;

    return data;
}

void extractSetCLIDData(QByteArray& data, CLID& ID)
{
    QDataStream in(data);

    in>>ID;
}

QByteArray serialiseSetCLIDData(CLID ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;

    return data;
}

void extractNewGMData(QByteArray& data, CLID& ID)
{
    QDataStream in(data);

    in>>ID;
}

QByteArray serialiseNewGMData(CLID ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;

    return data;
}

void extractVotedData(QByteArray& data, CLID& fID, CLID& tID)
{
    QDataStream in(data);

    in>>fID;
    in>>tID;
}

QByteArray serialiseVotedData(CLID fID, CLID tID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)fID;
    out<<(CLID)tID;

    return data;
}

void extractNewNickData(QByteArray& data, CLID& ID, QString& nick)
{
    QDataStream in(data);

    in>>ID;
    in>>nick;
}

QByteArray serialiseNewNickData(CLID ID, const QString& nick)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;
    out<<nick;

    return data;
}

void extractSetNickData(QByteArray& data, QString& nick)
{
    QDataStream in(data);

    in>>nick;
}

QByteArray serialiseSetNickData(const QString& nick)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<nick;

    return data;
}
