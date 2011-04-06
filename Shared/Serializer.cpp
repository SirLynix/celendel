#include "Serializer.h"
#include <QDebug>

#define QV(a) if(a.isEmpty()) return true;
#define R(a) if(a.status()!=QDataStream::Ok) return true;

QDataStream &operator<<(QDataStream & ds, const PlayerInformations& p)
{
    ds<<p.name<<p.ip;
    return ds;
}

QDataStream &operator>>(QDataStream & ds, PlayerInformations& p)
{
    ds>>p.name>>p.ip;
    return ds;
}

bool extractChatData(QByteArray& data, ENUM_TYPE& canal, QString& language, QString& text, CLID& sender)
{
    QV(data);
    QDataStream in(data);
    in>>canal;
    R(in);
    in>>text;
    R(in);
    in>>sender;
    R(in);

    return false;
}

QByteArray serialiseChatData(ENUM_TYPE canal, const QString& language, const QString& text, CLID sender)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(ENUM_TYPE)canal;
    out<<text;
    out<<(CLID)sender;
    return data;
}

bool extractErrorData(QByteArray& data, ENUM_TYPE& error_type, QString& text)
{
    QV(data);
    QDataStream in(data);

    in>>error_type;
    R(in);
    in>>text;
    R(in);
    return false;
}

QByteArray serialiseErrorData(ENUM_TYPE error_type, const QString& text)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(ENUM_TYPE)error_type;
    out<<text;

    return data;
}

bool extractGMElectData(QByteArray& data, CLID& ID)
{
    QV(data);
    QDataStream in(data);

    in>>ID;
    R(in);
    return false;
}

QByteArray serialiseGMElectData(CLID ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;

    return data;
}

bool extractSetCLIDData(QByteArray& data, CLID& ID)
{
    QV(data);
    QDataStream in(data);

    in>>ID;
    R(in);
    return false;
}

QByteArray serialiseSetCLIDData(CLID ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;

    return data;
}

bool extractNewGMData(QByteArray& data, CLID& ID)
{
    QV(data);
    QDataStream in(data);

    in>>ID;
    R(in);
    return false;
}

QByteArray serialiseNewGMData(CLID ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;

    return data;
}

bool extractVotedData(QByteArray& data, CLID& fID, CLID& tID)
{
    QV(data);
    QDataStream in(data);

    in>>fID;
    R(in);
    in>>tID;
    R(in);
    return false;
}

QByteArray serialiseVotedData(CLID fID, CLID tID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)fID;
    out<<(CLID)tID;

    return data;
}

bool extractNewNickData(QByteArray& data, CLID& ID, QString& nick)
{
    QV(data);
    QDataStream in(data);

    in>>ID;
    R(in);
    in>>nick;
    R(in);

    return false;
}

QByteArray serialiseNewNickData(CLID ID, const QString& nick)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;
    out<<nick;

    return data;
}

bool extractSetNickData(QByteArray& data, QString& nick)
{
    QV(data);
    QDataStream in(data);

    in>>nick;
    R(in);
    return false;
}

QByteArray serialiseSetNickData(const QString& nick)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<nick;

    return data;
}

bool extractGTFOLynixData(QByteArray& data, CLID& ID, ENUM_TYPE& dropType, QString& reason)
{
    QV(data);
    QDataStream in(data);

    in>>ID;
    R(in);
    in>>dropType;
    R(in);
    in>>reason;
    R(in);

    return false;
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

bool extractTODData(QByteArray& data, QString& when)
{
    QV(data);
    QDataStream in(data);

    in>>when;
    R(in);

    return false;
}

QByteArray serialiseTODData(const QString& when)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<when;

    return data;
}

bool extractLocationData(QByteArray& data, QString& where)
{
    QV(data);
    QDataStream in(data);

    in>>where;
    R(in);

    return false;
}

QByteArray serialiseLocationData(const QString& where)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<where;

    return data;
}

bool extractServerInformationsData(QByteArray& data, ServerInformations& si)
{
    QByteArray t=qUncompress(data);

    QV(t);

    QDataStream in(t);

    in>>si.players;
    R(in);
    in>>si.gameMasterID;
    R(in);
    in>>si.location;
    R(in);
    in>>si.timeOfDay;
    R(in);
    in>>si.gameStarted;
    R(in);
    in>>si.serverName;
    R(in);
    in>>si.motd;
    R(in);
    in>>si.narration;
    R(in);
    QByteArray l;
    in>>l;
    R(in);
    in>>si.languages;
    R(in);
    in>>si.dictionaries;
    R(in);
    in>>si.scriptList;
    R(in);

    return extractSyncLibsData(l, si.libs);
}

QByteArray serialiseServerInformationsData(const ServerInformations& si)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<si.players;
    out<<si.gameMasterID;
    out<<si.location;
    out<<si.timeOfDay;
    out<<si.gameStarted;
    out<<si.serverName;
    out<<si.motd;
    out<<si.narration;
    out<<serialiseSyncLibsData(si.libs);
    out<<si.languages;
    out<<si.dictionaries;
    out<<si.scriptList;

    return qCompress(data);
}

bool extractMOTDData(QByteArray& data, QString& motd)
{
    QByteArray t=qUncompress(data);
    QV(t);
    QDataStream in(t);

    in>>motd;
    R(in);

    return false;
}

QByteArray serialiseMOTDData(const QString& motd)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<motd;

    return qCompress(data);
}


bool extractMapInformationsData(QByteArray& data, MapInformations& mi)
{
    QByteArray d=qUncompress(data);
    QV(d);

    QDataStream in(d);

    in>>mi.name;
    R(in);

    qint32 size;
    in>>size;
    R(in);
    mi.mapItems.clear();
    for(int i=0; i<size; ++i)
    {
        mi.mapItems.append(MapItem());
        in>>mi.mapItems[i].coords;
        R(in);
        in>>mi.mapItems[i].rsid;
        R(in);
        in>>mi.mapItems[i].text;
        R(in);
        in>>mi.mapItems[i].color;
        R(in);
        in>>mi.mapItems[i].hidden;
        R(in);
    }

    qint32 mapX, mapY;
    in>>mapX>>mapY;
    R(in);

    mi.map.resize(mapDim(mapX, mapY));

    for(int x=0; x<mapX; ++x)
    {
        for(int y=0; y<mapY; ++y)
        {
            in>>mi.map[x][y];
            R(in);
        }
    }


    return false;
}

QByteArray serialiseMapInformationsData(const MapInformations& mi)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<mi.name;

    out<<(qint32)mi.mapItems.size();

    for(int i=0; i<mi.mapItems.size(); ++i)
    {
        out<<mi.mapItems[i].coords;
        out<<(RSID) mi.mapItems[i].rsid;
        out<<mi.mapItems[i].text;
        out<<mi.mapItems[i].color;
        out<<mi.mapItems[i].hidden;
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

    return qCompress(data);
}

bool extractMapItemsInformationsData(QByteArray& data, QList<MapItem>& mi)
{
    QByteArray t=qUncompress(data);
    QV(t);
    QDataStream in(t);

    qint32 size;
    in>>size;
    R(in);
    mi.clear();
    for(int i=0; i<size; ++i)
    {
        mi.append(MapItem());
        in>>mi[i].coords;
        R(in);
        in>>mi[i].rsid;
        R(in);
        in>>mi[i].text;
        R(in);
        in>>mi[i].color;
        R(in);
        in>>mi[i].hidden;
        R(in);
    }
    return false;
}

QByteArray serialiseMapItemsInformationsData(const QList<MapItem>& mi)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(qint32)mi.size();

    for(int i=0; i<mi.size(); ++i)
    {
        out<<mi[i].coords;
        out<<(RSID) mi[i].rsid;
        out<<mi[i].text;
        out<<mi[i].color;
        out<<mi[i].hidden;
    }

    return qCompress(data);
}

bool extractDiceRollData(QByteArray& data, CLID& ID, quint16& result)
{
    QV(data);
    QDataStream in(data);
    in>>ID;
    R(in);
    in>>result;
    R(in);

    return false;
}

QByteArray serialiseDiceRollData(CLID ID, quint16 result)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;
    out<<(quint16)result;

    return data;
}

bool extractPlaySoundData(QByteArray& data, QString& lib, QString& sound)
{
    QV(data);
    QDataStream in(data);
    in>>lib;
    R(in);
    in>>sound;
    R(in);

    return false;
}

QByteArray serialisePlaySoundData(const QString& lib, const QString& sound)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<lib;
    out<<sound;

    return data;
}

bool extractServerNameData(QByteArray& data, QString& name)
{
    QV(data);
    QDataStream in(data);
    in>>name;
    R(in);

    return false;
}

QByteArray serialiseServerNameData(const QString& name)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<name;

    return data;
}

bool extractClientJoinedData(QByteArray& data, CLID& ID, QString& IP)
{
    QV(data);
    QDataStream in(data);
    in>>ID;
    R(in);
    in>>IP;
    R(in);

    return false;
}

QByteArray serialiseClientJoinedData(const CLID& ID, const QString& IP)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;
    out<<IP;

    return data;
}

bool extractClientLeftData(QByteArray& data, CLID& ID)
{
    QV(data);
    QDataStream in(data);
    in>>ID;
    R(in);

    return false;
}

QByteArray serialiseClientLeftData(const CLID& ID)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<(CLID)ID;

    return data;
}

bool extractUnbanData(QByteArray& data, QString& IP)
{
    QV(data);
    QDataStream in(data);
    in>>IP;
    R(in);

    return false;
}

QByteArray serialiseUnbanData(const QString& IP)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<IP;

    return data;
}

bool extractAllNarrationData(QByteArray& data, QString& txt)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);
    in>>txt;
    R(in);

    return false;
}

QByteArray serialiseAllNarrationData(const QString& txt)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<txt;

    return qCompress(data);
}

bool extractSyncLibsData(QByteArray& data, QList<SoundLibInformations>& libs)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);
    int s=0;
    libs.clear();
    in>>s;
    R(in);
    for(int i=0;i<s;++i)
    {
        SoundLibInformations li;
        in>>li.name;
        R(in);
        in>>li.version;
        R(in);
        in>>li.sounds;
        R(in);
        libs.append(li);
    }

    return false;
}

QByteArray serialiseSyncLibsData(const QList<SoundLibInformations>& libs)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);


    out<<libs.size();
    for(int i=0;i<libs.size();++i)
    {
        out<<libs[i].name;
        out<<libs[i].version;
        out<<libs[i].sounds;
    }

    return qCompress(data);
}

bool extractLanguagesData(QByteArray& data, QList<QPair<QString, QString> >& languages)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    languages.clear();
    in>>languages;
    R(in);

    return false;
}

QByteArray serialiseLanguagesData(const QList<QPair<QString, QString> >& languages)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);


    out<<languages;

    return qCompress(data);
}

bool extractAddDicoData(QByteArray& data, QString& name, QString& content)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>name;
    R(in);
    in>>content;
    R(in);

    return false;
}

QByteArray serialiseAddDicoData(const QString& name, const QString& content)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<name;
    out<<content;

    return qCompress(data);
}

bool extractDicoListData(QByteArray& data, QStringList& names)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    names.clear();
    in>>names;
    R(in);

    return false;
}

QByteArray serialiseDicoListData(const QStringList& names)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<names;

    return qCompress(data);
}

bool extractRemoveDicoData(QByteArray& data, QString& name)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>name;
    R(in);


    return false;
}

QByteArray serialiseRemoveDicoData(const QString& name)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<name;

    return qCompress(data);
}


bool extractUpdateRessourcesData(QByteArray& data, QMap<QString, RSID>& ressources)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>ressources;
    R(in);


    return false;
}

QByteArray serialiseUpdateRessourcesData(const QMap<QString, RSID>& ressources)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<ressources;

    return qCompress(data);
}

bool extractScriptListData(QByteArray& data, QStringList& list)
{
    QByteArray d=qUncompress(data);
    QV(d);
    QDataStream in(d);

    in>>list;
    R(in);

    return false;
}

QByteArray serialiseScriptListData(const QStringList& list)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::ReadWrite);

    out<<list;

    return qCompress(data);
}
