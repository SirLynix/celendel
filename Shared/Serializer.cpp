#include "Serializer.h"
#include <QDataStream>
#include <QDebug>

void extractChatData(QByteArray& data, ENUM_TYPE& canal, QString& text, CLID& sender)
{
    QDataStream in(data);

    in>>canal;
    in>>text;
    in>>sender;
}

QByteArray serialiseChatData(ENUM_TYPE canal, const QString& text, CLID sender)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(ENUM_TYPE)canal;
    out<<text;
    out<<(CLID)sender;
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

void extractGTFOLynixData(QByteArray& data, CLID& ID, ENUM_TYPE& dropType, QString& reason)
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
    QByteArray t=qUncompress(data);
    QDataStream in(t);

    in>>si.playersName;
    in>>si.gameMasterID;
    in>>si.location;
    in>>si.timeOfDay;
    in>>si.gameStarted;
    in>>si.serverName;
    in>>si.motd;
    in>>si.narration;
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
    out<<si.motd;
    out<<si.narration;

    return qCompress(data);
}

void extractMOTDData(QByteArray& data, QString& motd)
{
    QByteArray t=qUncompress(data);
    QDataStream in(t);

    in>>motd;
}

QByteArray serialiseMOTDData(const QString& motd)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<motd;

    return qCompress(data);
}


void extractMapInformationsData(QByteArray& data, MapInformations& mi)
{
    QByteArray d=qUncompress(data);

    QDataStream in(d);


    qint32 size;
    in>>size;
    mi.mapItems.clear();
    for(int i=0; i<size; ++i)
    {
        mi.mapItems.append(MapItem());
        in>>mi.mapItems[i].coords.x;
        in>>mi.mapItems[i].coords.y;
        in>>mi.mapItems[i].pixID;
    }

    qint32 mapX, mapY;
    in>>mapX>>mapY;

    mi.map.resize(mapDim(mapX, mapY));

    for(int x=0; x<mapX; ++x)
    {
        for(int y=0; y<mapY; ++y)
        {
            in>>mi.map[x][y];
        }
    }

}

QByteArray serialiseMapInformationsData(const MapInformations& mi)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(qint32)mi.mapItems.size();

    for(int i=0; i<mi.mapItems.size(); ++i)
    {
        out<<(CELEM)mi.mapItems[i].coords.x;
        out<<(CELEM)mi.mapItems[i].coords.y;
        out<<(RSID) mi.mapItems[i].pixID;
    }

    qint32 mapX = sizeX(mi.map);
    qint32 mapY = sizeY(mi.map);

    out<<(qint32)mapX;
    out<<(qint32)mapY;

    for(int x=0; x<mapX; ++x)
    {
        for(int y=0; y<mapY; ++y)
        {
            out<<mi.map[x][y];
        }
    }

    return qCompress(data,1);
}

void extractMapItemsInformationsData(QByteArray& data, QList<MapItem>& mi)
{
    QDataStream in(data);

    qint32 size;
    in>>size;
    mi.clear();
    for(int i=0; i<size; ++i)
    {
        mi.append(MapItem());
        in>>mi[i].coords.x;
        in>>mi[i].coords.y;
        in>>mi[i].pixID;
    }
}

QByteArray serialiseMapItemsInformationsData(const QList<MapItem>& mi)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(qint32)mi.size();

    for(int i=0; i<mi.size(); ++i)
    {
        out<<(CELEM)mi[i].coords.x;
        out<<(CELEM)mi[i].coords.y;
        out<<(RSID) mi[i].pixID;
    }

    return data;
}

void extractDiceRollData(QByteArray& data, CLID& ID, quint16& result)
{
    QDataStream in(data);
    in>>ID;
    in>>result;
}

QByteArray serialiseDiceRollData(CLID ID, quint16 result)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;
    out<<(quint16)result;

    return data;
}

void extractPlaySoundData(QByteArray& data, RSID& ID)
{
    QDataStream in(data);
    in>>ID;
}

QByteArray serialisePlaySoundData(RSID ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(RSID)ID;

    return data;
}

void extractServerNameData(QByteArray& data, QString& name)
{
    QDataStream in(data);
    in>>name;
}

QByteArray serialiseServerNameData(const QString& name)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<name;

    return data;
}

void extractClientJoinedData(QByteArray& data, CLID& ID)
{
    QDataStream in(data);
    in>>ID;
}

QByteArray serialiseClientJoinedData(const CLID& ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;

    return data;
}

void extractClientLeftData(QByteArray& data, CLID& ID)
{
    QDataStream in(data);
    in>>ID;
}

QByteArray serialiseClientLeftData(const CLID& ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;

    return data;
}

void extractUnbanData(QByteArray& data, QString& IP)
{
    QDataStream in(data);
    in>>IP;
}

QByteArray serialiseUnbanData(const QString& IP)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<IP;

    return data;
}

void extractAllNarrationData(QByteArray& data, QString& txt)
{
    QByteArray d=qUncompress(data);

    QDataStream in(d);
    in>>txt;
}

QByteArray serialiseAllNarrationData(const QString& txt)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<txt;

    return qCompress(data);
}
