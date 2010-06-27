#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS

#define SERVER_IP "127.0.0.1"
#define MAX_CLIENTS 100
#define SERVER_PORT 5577
#define CLID quint16 /// Alias for Client ID.

#define qCApp QCoreApplication::instance()

#define ENUM_TYPE qint32

enum PACKET_TYPE { ERROR, CHAT, GM_ELECT, NEW_GM, LAUNCH_GAME, GAME_LAUNCHED, VOTED, SET_CLID, NEW_NICK, SET_NICK };
/* GM_ELECT type structure :
- CLID ID */

/* NEW_GM type structure :
- CLID ID */

/* SET_CLID type structure :
- CLID ID */

/* VOTED type structure :
- CLID From
- CLID To */

enum CANAL_TYPE { NORMAL, NARRATOR, RP, SELF_NARRATOR };
/* CHAT type structure :
- CANAL_TYPE canal
- QString text */

enum ERROR_TYPE { I_DONT_LIKE_LYNIX, ALREADY_VOTED, GAME_NOT_LAUNCHED, NOT_GM, INVALID_PACKET, INVALID_CANAL, CLIENT_DOES_NOT_EXIST };
/* ERROR type structure :
- ERROR_TYPE error
- QString text */

enum DROP_TYPE { KICKED, BANNED, CLIENTS_LIMIT_REACHED };

/*I_DONT_LIKE_LYNIX type structure :
- DROP_TYPE dtype
- QString reason*/

#define ETI(a) static_cast<ENUM_TYPE>(a)
// ETI means Enum To Integer. Just a cast.

#endif //Guard
