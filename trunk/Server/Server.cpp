#include "Server.h"
#include "..\Shared\Serializer.h"

Server::Server(QObject* parent) : QObject(parent)
{
    m_network=new ServerNetwork(this); //Start the network

    connect(m_network, SIGNAL(newClient(CLID)), this, SLOT(addClient(CLID)));
    connect(m_network, SIGNAL(clientGone(CLID)), this, SLOT(removeClient(CLID)));
    connect(m_network, SIGNAL(dataReceived(Packet*, CLID)), this, SLOT(processData(Packet*, CLID)));

    m_gameStarted=false;

}

Server::~Server()
{
    for(int i=0; i<m_players.size();++i)
        delete m_players[i];
}

/*void Server::processData(Packet* pa, CLID cID)*/
/// Moved in ServerSwitch.cpp


void Server::launchGame()
{
    m_gameStarted=true;
    m_network->sendToAll(ETI(GAME_LAUNCHED), QByteArray());
}

void Server::addClient(CLID cID)
{
    m_players.append(new Player(cID));
    log("Player "+QString::number(cID)+" added to game.");
}

Player* Server::getPlayer(CLID cID)
{
    for(int i=0; i<m_players.size();++i)
    {
        if(m_players[i]->ID()==cID)
        {
            return m_players[i];
        }
    }
    log("ERROR : Player "+QString::number(cID)+" not found !");
    return NULL;
}

void Server::removeClient(CLID cID)
{
    if(getPlayer(cID)==NULL)
        return;

    for(int i=0; i<m_players.size();++i)
    {
        if(m_players[i]->ID()==cID)
        {
            Player* ply=m_players[i];
            if(m_players[i]!=m_players.last()) //Put the pointer to the end of the list, for avoiding empty cases.
            {
                m_players[i]=m_players.last();
            }
            m_players.removeLast();
            delete ply;
            log("Player succefully removed from game.");
            return;
        }
    }
}
