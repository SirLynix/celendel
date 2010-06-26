#ifndef SERVER_H
#define SERVER_H

                    /// The main server class ///
 /* It rules the game. It receive data from the network class, */
/* Work on it, then answer with the network class once again. */

/* Workers :
    - Gigotdarnaud
*/

#include "Network.h"


class Server : public QObject
{
    Q_OBJECT
    public:
        Server(QObject* parent=NULL);


    private:
        ServerNetwork *m_network;

};

#endif // SERVER_H
