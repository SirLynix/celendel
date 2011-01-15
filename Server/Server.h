#ifndef SERVER_H
#define SERVER_H

                    /// The main server class ///
 /*  It rules the game. It receive data from the network class, */
/* Works on it, then answer with the network class once again. */

/* Workers :
    - Gigotdarnaud
*/

#include "Network.h"
#include <QList>
#include "Player.h"
#include "..\Shared\MapStructs.h"
#include "..\Shared\XML\person.h"
#include "Translator.h"

#define MOTD_DEFAULT_PATH "MOTD.html"

class Server : public QObject
{
    Q_OBJECT
    public:
        Server(QObject* parent=NULL);
        ~Server();

        Player* getPlayer(CLID cID);

        bool gameStarted() const {return m_gameStarted;}

        QString narration;
        QString serverName;
        QString location;
        QString timeOfDay;
        QString motd;

        bool changeGM(CLID cID); // Returns true on error

        ServerInformations getServerInformations() const;
        CLID nickToCLID(const QString& nick);

        QString translateText(const QString& text, const QString& language, CLID cID);

    public slots:
        void addClient(CLID cID);
        void removeClient(CLID cID);
        void launchGame();

    private slots:
        void cleanUp();
        void processData(std::auto_ptr<Packet>, CLID);

    private:
        ServerNetwork *m_network;
        QList<Player*> m_players;
        QList<QPair<Person*,Player*> > m_characters; //The first element is a character; the second is the player that control it.

        bool m_gameStarted;

        Translator m_translator;

        QList<SoundLibInformations> m_soundLibs;

        CLID m_GMID;

        MapInformations* m_map;

};

#endif // SERVER_H
