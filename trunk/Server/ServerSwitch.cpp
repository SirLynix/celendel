#include "Server.h"
#include "..\Shared\Serializer.h"
#include "..\Shared\Constants.h"

bool Server::changeGM(CLID cID)
{
    Player *ne=getPlayer(cID);
    if(ne==NULL)
        return true;

    Player *old=getPlayer(m_GMID);
    if(old!=NULL)
        old->unPromoteGM();

    m_GMID=cID;
    ne->promoteGM();
    m_network->sendToAll(ETI(NEW_GM), serialiseNewGMData(cID));

    log("The Game Master has been changed. ["+QString::number(ne->ID())+"]"+ne->nickname+" is now Game Master.");

    return false;
}

CLID Server::nickToCLID(const QString& nick)
{
    for(int i=0;i<m_players.size();++i)
    {
        if(nick==m_players[i]->nickname)
            return m_players[i]->ID();
    }
    return 0;
}

void Server::processData(Packet* pa, CLID cID)
{
    Player *ply = getPlayer(cID);
    if(ply==NULL)
    {
        delete pa;
        return;
    }
  //  log("Packet received.");
    switch(pa->type)
    {
        case CHAT:
        {
            ENUM_TYPE canal; QString text;
            CLID garbage;
            extractChatData(pa->data, canal, text, garbage);
            text=securise(text);
            log("Chat message received : ["+QString::number(ply->isGM())+"]"+ply->nickname+" say on ["+QString::number(canal)+"] : \""+text+"\"");
            switch(canal)
            {
                case ETI(NORMAL):
                {
                    text.truncate(MAX_MESSAGE_LENGHT);
                    text.replace('\n', "");
                    if(!text.isEmpty())
                        m_network->sendToAll(ETI(CHAT), serialiseChatData(ETI(NORMAL), text, cID));
                }
                break;
                case ETI(SELF_NARRATOR):
                {
                    if(gameStarted())
                    {
                        m_network->sendToAll(ETI(CHAT), serialiseChatData(ETI(SELF_NARRATOR), text, cID));
                    }
                    else
                    {
                        m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(GAME_NOT_LAUNCHED)));
                    }
                }
                break;
                case ETI(RP):
                {
                    if(gameStarted())
                    {
                        m_network->sendToAll(ETI(CHAT), serialiseChatData(ETI(RP), text, cID));
                    }
                    else
                    {
                        m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
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
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
        }
        break;
        case ALL_NARRATION:
        {
            if(ply->isGM())
            {
                extractAllNarrationData(pa->data, narration);
                m_network->sendToAll(ETI(ALL_NARRATION), serialiseAllNarrationData(narration));
            }
            else
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
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
                        m_GMID=winner->ID();
                        m_network->sendToAll(ETI(NEW_GM), serialiseNewGMData(winner->ID()));
                    }
                }
            }
        }
        break;
        case NEW_GM:
        {
            if(ply->isGM())
            {
                CLID tID;
                extractNewGMData(pa->data, tID);
                if(cID!=tID)
                {
                    Player*p=getPlayer(tID);
                    if(p==NULL)
                    {
                        m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(CLIENT_DOES_NOT_EXIST)));
                    }
                    else
                    {
                        changeGM(tID);
                }
                }
            }
            else
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
        }
        break;
        case SET_NICK:
        {
            QString nick;
            extractSetNickData(pa->data, nick);
            nick.replace(QRegExp("[^a-zA-Z0-9_'\\-יטאח]"), "");
            nick.truncate(MAX_NICKNAME_LENGHT);
            if(nick != "" && nickToCLID(nick) == 0)
            {
                log("Client [" + QString::number(ply->ID())+"] changed his nickname : \""+ply->nickname+"\" -> \"" +nick);
                ply->nickname=nick;
                m_network->sendToAll(ETI(NEW_NICK),serialiseNewNickData(ply->ID(),nick));
            }
        }
        break;
        case GTFO_LYNIX:
        {
            if(ply->isGM())
            {
                CLID tID=0;
                ENUM_TYPE kob=0;
                QString reason;
                extractGTFOLynixData(pa->data, tID, kob, reason);
                Player *tar = getPlayer(tID);

                if(tar==NULL)
                {
                    m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(CLIENT_DOES_NOT_EXIST)));
                }
                else
                {
                    switch(kob)
                    {
                        case KICK:
                            log("["+QString::number(cID)+"]" +ply->nickname+" kicked ["+QString::number(tID)+"]"+tar->nickname+". Reason : \""+reason);
                            m_network->kick(tID, reason);
                        break;
                        case BAN:
                            log("["+QString::number(cID)+"]"+ply->nickname+" kicked and banned ["+QString::number(tID)+"]"+tar->nickname+". Reason : \""+reason);
                            m_network->ban(tID, reason);
                        break;
                        default:
                            log("ERROR : Sanction unknown.");
                            m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(SANCTION_UNKNOWN)));
                        break;
                    }
                }
            }
            else
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
        }
        break;
        case UNBAN:
        {
            if(ply->isGM())
            {
                QString IP;
                extractUnbanData(pa->data, IP);
                m_network->unban(IP);
            }
            else
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
        }
        break;
        case TOD:
        {
            if(ply->isGM())
            {
                extractTODData(pa->data, timeOfDay);
                log("Game Master changed Time Of Day to : \""+timeOfDay+"\"");
                m_network->sendToAll(ETI(TOD), serialiseTODData(timeOfDay));
            }
            else
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
        }
        break;
        case LOCATION:
        {
            if(ply->isGM())
            {
                extractTODData(pa->data, location);
                log("Game Master changed location to : \""+location+"\"");
                m_network->sendToAll(ETI(LOCATION), serialiseTODData(location));
            }
            else
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
        }
        break;
        case PING:
        {
            m_network->sendToClient(cID, ETI(PING), QByteArray(), pa->timestamp, pa->ID);
        }
        break;
        case MAP_INFORMATIONS:
        {
            if(ply->isGM())
            {
                extractMapInformationsData(pa->data, *m_map);
                m_network->sendToAll(ETI(MAP_INFORMATIONS), serialiseMapInformationsData(*m_map));
            }
            else
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
        }
        break;
        case MAP_ITEMS_INFORMATIONS:
        {
            if(ply->isGM())
            {
                extractMapItemsInformationsData(pa->data, m_map->mapItems);
                m_network->sendToAll(ETI(MAP_ITEMS_INFORMATIONS), serialiseMapItemsInformationsData(m_map->mapItems));
            }
            else
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
        }
        break;
        case PLAY_SOUND:
        {
            if(ply->isGM())
            {
                m_network->sendToAll(pa, false);
            }
            else
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));
        }
        break;
        case ROLL_DICE:
        {
            m_network->sendToAll(ETI(ROLL_DICE), serialiseDiceRollData(cID, alea(1,20)));
        }
        break;
        case SERVER_NAME:
        {
            if(ply->isGM())
            {
                QString n;
                extractServerNameData(pa->data, n);
                n.replace(QRegExp("[^a-zA-Z0-9_]"), "");
                n.truncate(50);
                serverName=n;
                m_network->sendToAll(ETI(SERVER_NAME), serialiseServerNameData(n));
            }
            else
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));

        }
        break;
        case MOTD:
        {
            if(ply->isGM())
            {
                extractMOTDData(pa->data, motd);
                m_network->sendToAll(ETI(MOTD), serialiseMOTDData(motd));
            }
            else
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM)));

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
