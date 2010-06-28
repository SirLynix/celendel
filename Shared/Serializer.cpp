#include "Serializer.h"
#include <QDataStream>
#include <QDebug>
#include <ctime>
#include <cstdio>

int alea(int min,int max){static bool first=true;if(first){srand(time(NULL));first=false;alea(0,150);}return (int)(min+((float)rand()/RAND_MAX*(max-min+1)));}

quint32 sizeX(const MapArray& m)  { return (quint32)m.shape()[0];}
quint32 sizeY(const MapArray& m)  { return (quint32)m.shape()[1];}
quint32 sizeX(MapArray* m)  { return (quint32)m->shape()[0];}
quint32 sizeY(MapArray* m)  { return (quint32)m->shape()[1];}

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

void extractGTFOLynixData(QByteArray& data, CLID& ID, ENUM_TYPE dropType, QString& reason)
{
    QDataStream in(data);

    in>>ID;
    in>>dropType;
    in>>reason;
}

QByteArray serialiseGTFOLynixData(CLID ID, ENUM_TYPE dropType, const QString& reason)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;
    out<<(ENUM_TYPE)dropType;
    out<<reason;

    return data;
}

void extractTODData(QByteArray& data, QString& when)
{
    QDataStream in(data);

    in>>when;
}

QByteArray serialiseTODData(const QString& when)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<when;

    return data;
}

void extractLocationData(QByteArray& data, QString& where)
{
    QDataStream in(data);

    in>>where;
}

QByteArray serialiseLocationData(const QString& where)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<where;

    return data;
}

void extractServerInformationsData(QByteArray& data, ServerInformations& si)
{
    QDataStream in(data);

    in>>si.playersName;
    in>>si.gameMasterID;
    in>>si.location;
    in>>si.timeOfDay;
    in>>si.gameStarted;
    in>>si.serverName;
}

QByteArray serialiseServerInformationsData(const ServerInformations& si)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<si.playersName;
    out<<si.gameMasterID;
    out<<si.location;
    out<<si.timeOfDay;
    out<<si.gameStarted;
    out<<si.serverName;

    return data;
}

void extractMapInformationsData(QByteArray& data, MapInformations& mi)
{
    QDataStream in(data);

  /*  in>>mi.mapItems;
    in>>mi.map;*/

}

QByteArray serialiseMapInformationsData(const MapInformations& mi)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

   /* out<<mi.mapItems;

    out<<mi.map;*/

    return data;
}
