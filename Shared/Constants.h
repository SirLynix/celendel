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

#define MAX_SEQUENTIALS_PACKETS 15
#define PACKETS_COUNT_RESET_DELAY 100
#define MAX_PACKET_SIZE 1024*1024 //1Mio
#define SOCKET_BUFFER_SIZE 1024*1024*10 //10Mio

#define qCApp QCoreApplication::instance()

#define ENUM_TYPE qint32

#include "MapStructs.h"
#include <QStringList>
#include <QMap>
#include <QPair>
#include <QCryptographicHash>

#define QT_USE_FAST_CONCATENATION ///QString concatenate optimisation
#define QT_USE_FAST_OPERATOR_PLUS

QString hashFile(const QString& filename, QCryptographicHash::Algorithm al=QCryptographicHash::Sha1);
int alea(int min,int max);

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
//Q_DECLARE_METATYPE(PlayerInformations);

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
};

/* SERVER_INFORMATIONS type structure : (compressed)
- ServerInformations infos */

/* MAP_INFORMATIONS type structure :
- MapInformations mi */

/* MAP_ITEMS_INFORMATIONS type structure :
- QList<MapItem> listMi */


enum PACKET_TYPE { ERROR, PING, CHAT, ALL_NARRATION, GM_ELECT, NEW_GM, LAUNCH_GAME, GAME_LAUNCHED, VOTED, SET_CLID, NEW_NICK,
                SET_NICK, GTFO_LYNIX, TOD, LOCATION, SERVER_INFORMATIONS, MOTD, MAP_INFORMATIONS, MAP_ITEMS_INFORMATIONS,
                PLAY_SOUND, SCRIPTS_LIST, SCRIPTS_UPDATE, ROLL_DICE, SERVER_NAME, CLIENT_LEFT, CLIENT_JOINED, UNBAN, SYNC_LIBS, LANGUAGES_LIST};

#define MAX_NICKNAME_LENGHT 15
/* SCRIPT_LIST structure - compressed :
- QList<QPair<QString, QString> > list : first QString is the script filename, second is SHA-1 hash */

/* SCRIPT_UPDATE structure - compressed :
- QList<QPair<QString, QString> > list : first QString is the script filename, second is the script file data */

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
- quint16 result */

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

enum ERROR_TYPE { ALREADY_VOTED, GAME_NOT_LAUNCHED, NOT_GM, INVALID_PACKET, INVALID_CANAL, CLIENT_DOES_NOT_EXIST, CLIENTS_LIMIT_REACHED, SANCTION_UNKNOWN, CONNECTION_FAILED };
/* ERROR type structure :
- ERROR_TYPE error
- QString text */

enum DROP_TYPE { KICK, BAN };


///Gigotdarnaud : Yes, the "GTFO_LYNIX" constant kick or ban the targeted client.
///Lynix : What's wrong with you ?
/* GTFO_LYNIX type structure :
- CLID ID
- DROP_TYPE dtype
- QString reason*/

/* REQUEST_SANCTION type structure :
- CLID ID
- DROP_TYPE dtype
- QString reason*/

#define ETI(a) static_cast<ENUM_TYPE>(a)
// ETI means Enum To Integer. Just a cast.

#endif //Guard
