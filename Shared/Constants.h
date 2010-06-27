#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS

#define SERVER_IP "127.0.0.1"
#define MAX_CLIENTS 100
#define SERVER_PORT 5577
#define CLID quint32 /// Alias for Client ID.

#define ENUM_TYPE qint32

enum PACKET_TYPE { ERROR, CHAT, GM_ELECT, LAUNCH_GAME };

enum CANAL_TYPE { NORMAL, NARRATOR, RP };
/* CHAT type structure :
- CANAL_TYPE canal
- QString text */

enum ERROR_TYPE { I_DONT_LIKE_LYNIX, GAME_NOT_LAUNCHED, NOT_MJ, INVALID_PACKET, INVALID_CANAL };
/* ERROR type structure :
- ERROR_TYPE error
- QString text */

#define ETI(a) static_cast<ENUM_TYPE>(a)

#endif //Guard
