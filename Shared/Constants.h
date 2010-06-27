#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS

#define SERVER_IP "127.0.0.1"
#define MAX_CLIENTS 100
#define SERVER_PORT 5577
#define CLID quint32 /// Alias for Client ID.

#define qCApp QCoreApplication::instance()

#define ENUM_TYPE qint32

enum PACKET_TYPE { ERROR, CHAT, GM_ELECT, LAUNCH_GAME };

enum CANAL_TYPE { NORMAL, NARRATOR, RP, SELF_NARRATOR };
/* CHAT type structure :
- CANAL_TYPE canal
- QString text */

enum ERROR_TYPE { I_DONT_LIKE_LYNIX, GAME_NOT_LAUNCHED, NOT_GM, INVALID_PACKET, INVALID_CANAL };
/* ERROR type structure :
- ERROR_TYPE error
- QString text */

enum DROP_TYPE { KICKED, BANNED, CLIENTS_LIMIT_REACHED };

/*I_DONT_LIKE_LYNIX type structure :
- DROP_TYPE dtype
- QString reason*/

#define ETI(a) static_cast<ENUM_TYPE>(a)

#endif //Guard
