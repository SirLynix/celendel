#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS

                    /// The constants header ///
 /* Every constants, enums, macros are defined here. */
/* This header is link-free, global and shared. */

/* Workers :
    - Gigotdarnaud
*/

#define SERVER_IP "127.0.0.1" /// The default server IP - kinda useless
#define MAX_CLIENTS 100 /// An hard-coded client limit
#define SERVER_PORT 5577 /// The default server port, far less useless than the default IP
#define CLID quint16 /// Alias for CLient ID.
#define RSID qint32 /// Alias for ReSsource ID.
#define LVER qint32 ///Alias for Lib VERsion.
#define ENID qint32 ///Alias for ENtity ID.

#define MAX_SEQUENTIALS_PACKETS 15
#define PACKETS_COUNT_RESET_DELAY 100
#define MAX_PACKET_SIZE 1024*1024 //1Mio
#define SOCKET_BUFFER_SIZE 1024*1024*10 //10Mio

#define DICTIONARIES_FOLDER_PATH QString("dictionaries/")
#define DICTIONARIES_EXTENSION QString(".dic")

#define qCApp QCoreApplication::instance()

#include <QDebug>
#ifdef __func__
    #define DEB() qDebug() << __FILE__ << " " << __func__ << " " << __LINE__ << "\t: "
#elif defined __FUNCTION__
    #define DEB() qDebug() << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << "\t: "
#else
    #define DEB() qDebug() << __FILE__ << " " << __LINE__ << "\t: "
#endif

#define ENUM_TYPE qint32

#include "MapStructs.h"
#include <QStringList>

#include <QMap>

#include <QList>
#include <QPair>

#include <QVariant>

#define QT_USE_FAST_CONCATENATION ///QString concatenate optimisation
#define QT_USE_FAST_OPERATOR_PLUS

#include <QCryptographicHash>
QString hashFile(const QString& filename, QCryptographicHash::Algorithm al=QCryptographicHash::Sha1);
int alea(int min,int max);

bool mkpath(const QString& s);

QStringList listFilesInFolder(const QString& folder, const QStringList& filters, const QString& suff="");
QStringList listFilesInFolder(const QString& folder, const QString& filter="");

template < typename T>

bool resize(QList<T>& l, int size, const T& def=T())
{
    if(size<0)
        return true;


    int m=l.size();

    if(size>m)
    {
        for(int i=m;i<size;++i)
            l.append(def);
    }
    else if(size<m)
    {
        for(int i=m-size;i>0;--i)
            l.removeLast();
    }


    return false;
}

quint32 sizeX(const MapArray& m);
quint32 sizeY(const MapArray& m);
quint32 sizeX(MapArray* m);
quint32 sizeY(MapArray* m);

struct SoundLibInformations
{
    SoundLibInformations() {version=-1;}
    LVER version;
    QString name;
    QStringList sounds;
};

struct PlayerInformations
{
    PlayerInformations(QString a_name="", QString a_ip=""):name(a_name),ip(a_ip) {}
    QString name;
    QString ip;
};


typedef QPair<QString, QString> QStringPair;
Q_DECLARE_METATYPE(QStringPair);
typedef QList<QStringPair> QStringPairList;
Q_DECLARE_METATYPE(QStringPairList);

struct EntityData
{
    EntityData() {}
    EntityData(QVariant d) { data = d; }

    QString shownName;

    bool isString() const { return data.type() == QVariant::String; }
    bool isNumber() const { return data.type() == QVariant::Double; }
    bool isStringPairList() const { return data.canConvert<QStringPairList>(); }

    QString getString() const { return data.toString(); }
    double getNumber() const { return data.toDouble(); }
    QStringPairList getStringPairList() const { return data.value<QStringPairList >(); }

    void setData(const QString& s) { data.setValue(s); }
    void setData(const QStringPairList& s) { data.setValue(s); }
    void setData(double d) { data.setValue(d); }

    /* Note that if the data can be converted to a QString (e.i. a number), getString() will return the converted value. */

    private:
        friend QDataStream &operator<<(QDataStream & ds, const EntityData& p);
        friend QDataStream &operator>>(QDataStream & q, EntityData& p);
        QVariant data;
};

struct EntityInformations
{
    QString name;
    QMap<QString, EntityData> data;
};

struct ServerInformations
{
    QMap<CLID,PlayerInformations> players;
    CLID gameMasterID;
    QString location;
    QString timeOfDay;
    quint16 gameStarted;
    QString serverName;
    QString motd;
    QString narration;
    QList<SoundLibInformations> libs;
    QList<QPair<QString, QString> > languages;
    QStringList dictionaries;
    QStringList scriptList;
};

/* SERVER_INFORMATIONS type structure : (compressed)
- ServerInformations infos */

/* MAP_INFORMATIONS type structure :
- MapInformations mi */

/* MAP_ITEMS_INFORMATIONS type structure :
- QList<MapItem> listMi */


enum PACKET_TYPE { ERROR, PING, CHAT, ALL_NARRATION, GM_ELECT, NEW_GM, LAUNCH_GAME, GAME_LAUNCHED, VOTED, SET_CLID, NEW_NICK,
                SET_NICK, GTFO_LYNIX, TOD, LOCATION, SERVER_INFORMATIONS, MOTD, MAP_INFORMATIONS, MAP_ITEMS_INFORMATIONS,
                PLAY_SOUND, ROLL_DICE, SERVER_NAME, CLIENT_LEFT, CLIENT_JOINED, UNBAN, SYNC_LIBS, SCRIPTS_LIST, RENAME_SCRIPT,
                LANGUAGES_LIST, DICO_LIST, ADD_DICO, REMOVE_DICO, UPDATE_RESSOURCES, SEND_SCRIPT, REQUEST_SCRIPT_UPDATE, DELETE_SCRIPT,
                ENTITIES_INFORMATIONS, UPDATE_ENTITY_INFORMATIONS, CREATE_ENTITY, DELETE_ENTITY, INJECT_CODE, SCRIPT_MESSAGE, UPDATE_CHARACTER_LIST, MAP_FLARE };

#define MAX_NICKNAME_LENGHT 15

/* MAP_FLARE structure :
- QPoint coords
- CLID who           */

/* UPDATE_RESSOURCES structure - compressed :
- QMap<QString, RSID> ressources */

/* DICO_LIST structure - compressed :
- QStringList names */

/* ADD_DICO structure - compressed :
- QString name
- QString content */

/* INJECT_CODE structure - compressed :
- QString entityName
- QString code */

enum SCRIPT_MESSAGE_TYPE { ERROR_MSG, TO_GM, TO_OWNER, ACTION_TO_DO, TO_PLAYER, TO_ALL };

/* SCRIPT_MESSAGE structure - compressed:
- SCRIPT_MESSAGE_TYPE type
- QString ent
- QString message */

/* UPDATE_CHARACTER_LIST structure - compressed :
- QStringList list */

/* ENTITIES_INFORMATIONS structure - compressed :
- QList<EntityInformations> entityList */

/* UPDATE_ENTITY_INFORMATIONS structure - compressed :
- EntityInformations entityInfo */

/* CREATE_ENTITY structure :
- QString name
- QString scriptName */

/* DELETE_ENTITY structure :
- QString name */

/* SCRIPTS_LIST structure - compressed :
- QStringlist scripts */

/* SEND_SCRIPT structure - compressed :
- QString name
- QString content */

/* REQUEST_SCRIPT_UPDATE structure :
- QString name */

/* RENAME_SCRIPT structure :
- QString name
- QString newName */

/* DELETE_SCRIPT structure :
- QString name */

/* REMOVE_DICO structure - compressed :
- QString name */

/* LANGUAGES_LIST structure :
- QList<QPair<QString, QString> > languages */

/* SYNC_LIBS structure :
- QList<SoundLibInformations> libs */

/* CLIENT_LEFT structure :
- CLID ID */

/* CLIENT_JOIGNED structure :
- CLID ID
- QString IP */

/* MOTD structure - compressed :
- QString motd */

/* UNBAN structure :
- QString IP */

/* SERVER_NAME type structure :
- QString name */

/* ROLL_DICE type structure :
- CLID ID
- quint16 result
- quint16 max */

/* PLAY_SOUND type structure :
- QString lib
- QString sound */

/* GM_ELECT type structure :
- CLID ID */


/* NEW_GM type structure :
- CLID ID */

/* SET_CLID type structure :
- CLID ID */

/* TOD type structure :
- QString when */

/* LOCATION type structure :
- QString where */

/* VOTED type structure :
- CLID From
- CLID To */

enum CANAL_TYPE { NORMAL, RP, SELF_NARRATOR };
#define MAX_MESSAGE_LENGHT 1024
/* CHAT type structure :
- CANAL_TYPE canal
- QString text
- CLID sender */

enum ERROR_TYPE { ALREADY_VOTED, GAME_NOT_LAUNCHED, NOT_GM, INVALID_PACKET, INVALID_CANAL, CLIENT_DOES_NOT_EXIST, INVALID_NICKNAME,
            CLIENTS_LIMIT_REACHED, SANCTION_UNKNOWN, CONNECTION_FAILED, CANNOT_LOAD_LANGUAGE, CANNOT_LOAD_DICTIONARY, CANNOT_REMOVE_DICTIONARY,
            CANNOT_UPDATE_SCRIPT, CANNOT_OPEN_SCRIPT, CANNOT_RENAME_SCRIPT, CANNOT_DELETE_SCRIPT, CANNOT_CREATE_ENTITY, ENTITY_NOT_FOUND, NO_CHARACTER };
/* ERROR type structure :
- ERROR_TYPE error
- QString text */

enum DROP_TYPE { KICK, BAN };


/* GTFO_LYNIX type structure :
- CLID ID
- DROP_TYPE dtype
- QString reason*/


#define ETI(a) static_cast<ENUM_TYPE>(a)
// ETI means Enum To Integer. Just a cast.

#endif //Guard
