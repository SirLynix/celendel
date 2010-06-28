#ifndef SERVER_H
#define SERVER_H

                    /// The main server class ///
 /* It rules the game. It receive data from the network class, */
/* Work on it, then answer with the network class once again. */

/* Workers :
    - Gigotdarnaud
*/

#include "Network.h"
#include <QList>
#include "Player.h"
#include "..\Shared\MapStructs.h"

class Server : public QObject
{
    Q_OBJECT
    public:
        Server(QObject* parent=NULL);
        ~Server();

        Player* getPlayer(CLID cID);

        bool gameStarted() const {return m_gameStarted;}

        QString serverName;
        QString location;
        QString timeOfDay;

        bool changeGM(CLID cID); // Returns true if error

        ServerInformations getServerInformations() const;

    public slots:
        void addClient(CLID cID);
        void removeClient(CLID cID);
        void processData(Packet*, CLID);
        void launchGame();

    private:
        ServerNetwork *m_network;
        QList<Player*> m_players;
        bool m_gameStarted;

        CLID m_GMID;

        MapInformations m_map;

};

#endif // SERVER_H
