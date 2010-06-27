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
    log("Packet received.");
    switch(pa->type)
    {
        case CHAT:
        {
            ENUM_TYPE canal; QString text;
            extractChatData(pa->data, canal, text);
            log("Chat message received : ["+QString::number(ply->isGM())+"]"+ply->nickname+" say on ["+QString::number(canal)+"] : \""+text+"\"");
            switch(canal)
            {
                case ETI(NORMAL):
                {
                    m_network->sendToAll(ETI(CHAT), serialiseChatData(ETI(NORMAL), text));
                }
                break;
                case ETI(NARRATOR):
                {
                    if(ply->isGM())
                    {
                        m_network->sendToAll(ETI(CHAT), serialiseChatData(ETI(NARRATOR), text));
                    }
                    else
                    {
                        m_network->sendToAll(ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
                    }
                }
                break;
                case ETI(SELF_NARRATOR):
                {
                    if(gameStarted())
                    {
                        m_network->sendToAll(ETI(CHAT), serialiseChatData(ETI(SELF_NARRATOR), text));
                    }
                    else
                    {
                        m_network->sendToAll(ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
                    }
                }
                break;
                case ETI(RP):
                {
                    if(gameStarted())
                    {
                        m_network->sendToAll(ETI(CHAT), serialiseChatData(ETI(RP), text));
                    }
                    else
                    {
                        m_network->sendToAll(ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
                    }
                }
                break;
                default:
                {
                    log("ERROR : Canal unknown !");
                    m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(INVALID_CANAL)));
                }
                break;
            }
        }
        break;
        case ERROR:
        {
            log("ERROR : Client sent an error.");
        }
        break;
        case LAUNCH_GAME:
        {
            if(ply->isGM() && !gameStarted())
            {
                launchGame();
            }
            else
                m_network->sendToAll(ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
        }
        break;
        case GM_ELECT:
        {
            log("Client "+QString::number(cID)+" voted !");
            CLID vID;
            extractGMElectData(pa->data, vID);
            Player *vp=getPlayer(vID);
            if(vp==NULL)
            {
                m_network->sendToAll(ETI(ERROR), serialiseErrorData(ETI(CLIENT_DOES_NOT_EXIST)));
            }
            else
            {
                if(ply->vote(vp))
                {
                    m_network->sendToAll(ETI(ERROR), serialiseErrorData(ETI(ALREADY_VOTED)));
                }
                else
                {
                    m_network->sendToAll(ETI(VOTED), serialiseVotedData(cID, vID));
                    quint16 votes=0;

                    for(int i=0;i<m_players.size();++i)
                        votes+=m_players[i]->voteCount();

                    if(votes==m_players.size()*4/3)
                    {
                        QList<Player*> winners;
                        winners.append(m_players.first());
                        for(int i=0;i<m_players.size();++i)
                        {
                            if(m_players[i]->voteCount()>winners.first()->voteCount())
                            {
                                winners.clear();
                                winners.append(m_players[i]);
                            }
                            else if(m_players[i]->voteCount()==winners.first()->voteCount())
                            {
                                winners.append(m_players[i]);
                            }
                            m_players[i]->voteEnded();
                        }
                        Player* winner = winners[alea(0,winners.size()-1)];
                        log("Client " + QString::number(winner->ID()) + " has been elected GM !");
                        winner->promoteGM();
                        m_network->sendToAll(ETI(NEW_GM), serialiseNewGMData(winner->ID()));
                    }
                }
            }
        }
        break;
        case SET_NICK:
        {
            QString nick;
            extractSetNickData(pa->data, nick);
            log("Client [" + QString::number(ply->ID())+"] changed his nickname : \""+ply->nickname+"\" -> \"" +nick);
            ply->nickname=nick;
            m_network->sendToAll(ETI(NEW_NICK),serialiseNewNickData(ply->ID(),nick));
        }
        break;
        default:
        {
            log("ERROR : packet type "+QString::number(pa->type)+" unknown ! (from Client "+QString::number(cID)+")");
            m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(INVALID_PACKET)));
        }
        break;
    }

    delete pa;
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
