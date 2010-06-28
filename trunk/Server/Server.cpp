#include "Server.h"
#include "..\Shared\Serializer.h"

Server::Server(QObject* parent) : QObject(parent)
{
    m_network=new ServerNetwork(this); //Start the network

    connect(m_network, SIGNAL(newClient(CLID)), this, SLOT(addClient(CLID)));
    connect(m_network, SIGNAL(clientGone(CLID)), this, SLOT(removeClient(CLID)));
    connect(m_network, SIGNAL(dataReceived(Packet*, CLID)), this, SLOT(processData(Packet*, CLID)));

    m_gameStarted=false;
    m_GMID=0;

}

Server::~Server()
{
    for(int i=0; i<m_players.size();++i)
        delete m_players[i];
}

/*void Server::processData(Packet* pa, CLID cID)*/
/// Moved in ServerSwitch.cpp

ServerInformations Server::getServerInformations() const
{
    ServerInformations si;
    for(int i=0;i<m_players.size();++i)
        si.playersName[m_players[i]->ID()]=m_players[i]->nickname;
    si.gameMasterID=m_GMID;
    si.location=location;
    si.timeOfDay=timeOfDay;
    si.gameStarted=gameStarted();
    si.serverName=serverName;

    return si;
}

void Server::launchGame()
{
    m_gameStarted=true;
    m_network->sendToAll(ETI(GAME_LAUNCHED), QByteArray());
}

void Server::addClient(CLID cID)
{
    m_players.append(new Player(cID));
    log("Player "+QString::number(cID)+" added to game.");
    m_network->sendToAll(ETI(SERVER_INFORMATIONS), serialiseServerInformationsData(getServerInformations()));
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

            if(ply->isGM()&&m_players.size())
                changeGM(m_players[0]->ID());

            ply->deleteLater();
            log("Player succefully removed from game.");
            return;
        }
    }
}
