#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS

                    /// The constants headers ///
 /* Every constants, enums, macros are defined here. */
/* This header is link-free, global and shared. */

/* Workers :
    - Gigotdarnaud
*/

#define SERVER_IP "127.0.0.1"
#define MAX_CLIENTS 100
#define SERVER_PORT 5577
#define CLID quint16 /// Alias for Client ID.
#define RSID quint16 /// Alias for Ressource ID.

#define qCApp QCoreApplication::instance()

#define ENUM_TYPE qint32

#include <QMap>
#include <QString>
#include <Boost/multi_array.hpp>

struct ServerInformations
{
    QMap<CLID,QString> playersName;
    CLID gameMasterID;
    QString location;
    QString timeOfDay;
    quint16 gameStarted;
    QString serverName;
};

#define CELEM quint32

struct Coords
{
    Coords(CELEM a=0, CELEM b=0): x(a), y(b) {}
    CELEM x;
    CELEM y;
};

struct MapItem
{
    Coords coords;
    RSID pixID;
};

typedef boost::multi_array<RSID, 2> MapArray;
#define mapDim(x,y) boost::extents[x][y]

struct MapInformations
{
    MapInformations(){map=NULL;}
    QList<MapItem> mapItems;
    MapArray* map;

    private:
        MapInformations(const MapInformations&); ///Non copiable
};

/* MAP_INFORMATIONS type structure :
- MapInformations mi */

/* MAP_ITEMS_INFORMATIONS type structure :
- QList<MapItem> listMi */

enum RESS_INFO_TYPE { TILES, SOUNDS };

/* RESSOURCES_INFORMATIONS type structure :
- RESS_INFO_TYPE type
- QByteArray ress  /!\Serialized and compressed data/!\ : QList<QByteArray>*/

enum PACKET_TYPE { ERROR, PING, CHAT, GM_ELECT, NEW_GM, LAUNCH_GAME, GAME_LAUNCHED, VOTED, SET_CLID, NEW_NICK,
                SET_NICK, GTFO_LYNIX, TOD, LOCATION, SERVER_INFORMATIONS, MAP_INFORMATIONS, MAP_ITEMS_INFORMATIONS, RESSOURCES_INFORMATIONS};



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

enum CANAL_TYPE { NORMAL, NARRATOR, RP, SELF_NARRATOR };
/* CHAT type structure :
- CANAL_TYPE canal
- QString text */

enum ERROR_TYPE { ALREADY_VOTED, GAME_NOT_LAUNCHED, NOT_GM, INVALID_PACKET, INVALID_CANAL, CLIENT_DOES_NOT_EXIST, CLIENTS_LIMIT_REACHED, SANCTION_UNKNOWN };
/* ERROR type structure :
- ERROR_TYPE error
- QString text */

enum DROP_TYPE { KICK, BAN };

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
