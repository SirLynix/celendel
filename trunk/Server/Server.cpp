#include "Server.h"
#include <QTimer>
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

void Server::processData(Packet* pa, CLID cID)
{
    Player *ply = getPlayer(cID);
    if(ply==NULL)
    {
        delete pa;
        return;
    }

    switch(pa->type)
    {
        case CHAT:
        {
            ENUM_TYPE canal; QString text;
            extractChatData(pa->data, canal, text);
            log("Chat message received : ["+QString::number(ply->isGM())+"]"+ply->name+" say on ["+QString::number(canal)+"] : \""+text+"\"");
            switch(canal)
            {

                default:
                {
                    log("ERROR : Canal unknown !");
                    m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(INVALID_CANAL)));
                }
                break;
            }
        }
        break;
        default:
        {
            log("ERROR : packet type "+QString::number(pa->type)+" unknown ! (from Client "+QString::number(cID)+")");
        }
        break;
    }

    delete pa;
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
