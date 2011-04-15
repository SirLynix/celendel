#include "Server.h"
#include "../Shared/Serializer.h"
#include "../Shared/Constants.h"

#define QE(a) if(a) {log("ERROR : packet received corrupted ! (from Client "+QString::number(cID)+") at line "+QString::number(__LINE__)+" in file "__FILE__); m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(INVALID_PACKET))); m_network->blame(cID); return;}
#define GM_CHECK() if(!ply->isGM()) { m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(NOT_GM))); log("POWER ERROR : client "+QString::number(cID)+" at line "+QString::number(__LINE__)+" in file "__FILE__); return;}

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



QString Server::translateText(const QString& text, const QString& language, CLID cID)
{
  //  Player* ply=getPlayer(cID);

    int prct=0;
/*
    if(ply->currentCharacter!=NULL)
    {
        prct=ply->currentCharacter->abilityInLanguage(language);
    }*/

    return m_translator.translate(text, language, prct);
}

void Server::processData(std::auto_ptr<Packet> pa, CLID cID)
{
    Player *ply = getPlayer(cID);
    if(ply==NULL)
    {
        log("ERROR : Packet received, but player is unfindable (cast error). -> trash bin, sorry little orphan packet.");
        return;

    }
    QE(pa.get()==NULL);
    QE(pa->error());

    //  log("Packet received, working...");
    switch(pa->type)
    {
        case CHAT:
        {
            ENUM_TYPE canal; QString text; QString lang;
            CLID garbage;
            QE(extractChatData(pa->data, canal, lang, text, garbage));
            text=securise(text);
            if(!text.isEmpty())
            {
                log("Chat message received : [GM="+QString::number(ply->isGM())+"]"+ply->nickname+" say on ["+QString::number(canal)+"] : \""+text+"\"");
                switch(canal)
                {
                    case ETI(NORMAL):
                    {
                        text.truncate(MAX_MESSAGE_LENGHT);
                        text.replace('\n', "");
                        if(!text.isEmpty())
                            m_network->sendToAll(ETI(CHAT), serialiseChatData(ETI(NORMAL), "", text, cID));
                    }
                    break;
                    case ETI(SELF_NARRATOR):
                    {
                        if(gameStarted())
                        {
                            m_network->sendToAll(ETI(CHAT), serialiseChatData(ETI(SELF_NARRATOR), "", text, cID));
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
                            if(lang!="")
                            {
                                for(int i=0,m=m_players.size();i<m;++i)
                                {
                                    m_network->sendToClient(m_players[i]->ID(), ETI(CHAT), serialiseChatData(ETI(RP), lang, translateText(text, lang, m_players[i]->ID()), cID));
                                }
                            }
                            else
                            {
                                m_network->sendToAll(ETI(CHAT), serialiseChatData(ETI(RP), lang, text, cID));
                            }
                        }
                        else
                        {
                            m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(GAME_NOT_LAUNCHED)));
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
        }
        break;
        case ERROR:
        {
            log("ERROR : Client sent an error.");
        }
        break;
        case LAUNCH_GAME:
        {
            GM_CHECK();
            launchGame();
        }
        break;
        case ALL_NARRATION:
        {
            GM_CHECK();
            QE(extractAllNarrationData(pa->data, narration));
            m_network->sendToAll(ETI(ALL_NARRATION), serialiseAllNarrationData(narration));
        }
        break;
        case GM_ELECT:
        {
            log("Client "+QString::number(cID)+" voted !");
            CLID vID;
            QE(extractGMElectData(pa->data, vID));
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
            GM_CHECK();
            CLID tID;
            QE(extractNewGMData(pa->data, tID));
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
        break;
        case SET_NICK:
        {
            QString nick;
            QE(extractSetNickData(pa->data, nick));
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
            GM_CHECK();
            CLID tID=0;
            ENUM_TYPE kob=0;
            QString reason;
            QE(extractGTFOLynixData(pa->data, tID, kob, reason));
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
        break;
        case UNBAN:
        {
            GM_CHECK();
            QString IP;
            QE(extractUnbanData(pa->data, IP));
            m_network->unban(IP);
        }
        break;
        case TOD:
        {
            GM_CHECK();
            QE(extractTODData(pa->data, timeOfDay));
            log("Game Master changed Time Of Day to : \""+timeOfDay+"\"");
            m_network->sendToAll(ETI(TOD), serialiseTODData(timeOfDay));
        }
        break;
        case LOCATION:
        {
            GM_CHECK();
            QE(extractTODData(pa->data, location));
            log("Game Master changed location to : \""+location+"\"");
            m_network->sendToAll(ETI(LOCATION), serialiseTODData(location));
        }
        break;
        case PING:
        {
            m_network->sendToClient(cID, ETI(PING), QByteArray(), pa->timestamp, pa->ID);
        }
        break;
        case MAP_INFORMATIONS:
        {
            GM_CHECK();
            QE(extractMapInformationsData(pa->data, *m_map));
            m_network->sendToAll(ETI(MAP_INFORMATIONS), serialiseMapInformationsData(*m_map));
            log("Game Master changed the map.");
        }
        break;
        case UPDATE_RESSOURCES:
        {
            GM_CHECK();
            QE(extractUpdateRessourcesData(pa->data, m_ressources));
            m_network->sendToAll(ETI(UPDATE_RESSOURCES), serialiseUpdateRessourcesData(m_ressources));
            log("Game Master modified the ressource set.");
        }
        break;
        case MAP_ITEMS_INFORMATIONS:
        {
            GM_CHECK();
            QE(extractMapItemsInformationsData(pa->data, m_map->mapItems));
            m_network->sendToAll(ETI(MAP_ITEMS_INFORMATIONS), serialiseMapItemsInformationsData(m_map->mapItems));
        }
        break;
        case PLAY_SOUND:
        {
            GM_CHECK();
            m_network->sendToAll(/*pa*/pa.get(), false);
        }
        break;
        case ROLL_DICE:
        {
            CLID g;
            quint16 v, max;
            QE(extractDiceRollData(pa->data, g, v, max));
            if(max>1)
                m_network->sendToAll(ETI(ROLL_DICE), serialiseDiceRollData(cID, alea(1,max), max));
        }
        break;
        case SERVER_NAME:
        {
            GM_CHECK();
            QString n;
            QE(extractServerNameData(pa->data, n));
            n.replace(QRegExp("[^a-zA-Z0-9_]"), "");
            n.truncate(50);
            serverName=n;
            m_network->sendToAll(ETI(SERVER_NAME), serialiseServerNameData(n));
        }
        break;
        case SYNC_LIBS:
        {
            GM_CHECK();
            QList<SoundLibInformations> l;
            QE(extractSyncLibsData(pa->data, l));

            m_network->sendToAll(ETI(SYNC_LIBS), serialiseSyncLibsData(l));
            m_soundLibs=l;

        }
        break;
        case MOTD:
        {
            GM_CHECK();
            QE(extractMOTDData(pa->data, motd));
            m_network->sendToAll(ETI(MOTD), serialiseMOTDData(motd));

        }
        break;
        case LANGUAGES_LIST:
        {
            GM_CHECK();
            QList<QPair<QString,QString> > l;
            QE(extractLanguagesData(pa->data, l));

            for(int i=0,size=l.size();i<size;++i)
            {
                if(m_translator.loadLanguage(l[i].first, l[i].second))
                {
                    m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(CANNOT_LOAD_LANGUAGE), l[i].first));
                }
            }
            m_network->sendToAll(ETI(LANGUAGES_LIST), serialiseLanguagesData(m_translator.getLanguages()));
        }
        break;
        case ADD_DICO:
        {
            GM_CHECK();
            QString name, content;
            QE(extractAddDicoData(pa->data, name, content));

            if(m_translator.loadDictionary(name, content))
            {
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(CANNOT_LOAD_DICTIONARY), name));
            }
            else
                m_network->sendToAll(ETI(DICO_LIST), serialiseDicoListData(m_translator.getDictionariesList()));
        }
        break;
        case REMOVE_DICO:
        {
            GM_CHECK();
            QString name;
            QE(extractRemoveDicoData(pa->data, name));

            if(m_translator.removeDictionary(name))
            {
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(CANNOT_REMOVE_DICTIONARY), name));
            }
            else
                m_network->sendToAll(ETI(DICO_LIST), serialiseDicoListData(m_translator.getDictionariesList()));
        }
        break;
        case SCRIPTS_LIST:
        {
            sendScriptList(cID);
        }
        break;
        case SEND_SCRIPT:
        {
            GM_CHECK();
            QString name, content;
            QE(extractSendScriptData(pa->data, name, content));

            if(!updateScript(name, content))
            {
                sendScriptList(cID);
            }
            else
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(CANNOT_UPDATE_SCRIPT), name));

        }
        break;
        case REQUEST_SCRIPT_UPDATE:
        {
            GM_CHECK();
            QString name;
            QE(extractRequestScriptData(pa->data, name));
            QFile file (SCRIPT_FOLDER+name);
            if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(CANNOT_OPEN_SCRIPT), name));
            }
            else
            {
                m_network->sendToClient(cID, ETI(SEND_SCRIPT), serialiseSendScriptData(name, file.readAll()));
            }

        }
        break;
        case DELETE_SCRIPT:
        {
            GM_CHECK();
            QString name;
            QE(extractDeleteScriptData(pa->data, name));
            if(isValidScriptName(name) && QFile::remove(SCRIPT_FOLDER+name))
            {
                log("GM removed script \"" + name + "\" from hard drive.");
                sendScriptList(cID);
            }
            else
            {
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(CANNOT_DELETE_SCRIPT), name));
            }
        }
        break;
        case RENAME_SCRIPT:
        {
            GM_CHECK();
            QString name, newName;
            QE(extractRenameScriptData(pa->data, name, newName));

            QFile f(SCRIPT_FOLDER+name);
            if(isValidScriptName(name) && isValidScriptName(newName))
            {
                mkscriptpath(newName);
                f.rename(SCRIPT_FOLDER+newName);
                log("GM renamed script \"" + name + "\" to \"" + newName + "\"");
                sendScriptList(cID);
            }
            else
            {
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(CANNOT_RENAME_SCRIPT), name));
            }
        }
        break;
        case CREATE_ENTITY:
        {
            GM_CHECK();
            QString name, scriptName;
            QE(extractCreateEntityData(pa->data, name, scriptName));
            if(!m_scripts.makeEntity(name, SCRIPT_FOLDER+scriptName))
            {
                log("GM succefully created new entity \"" + name + "\" from script \"" + scriptName + "\"");
                m_network->sendToAll(ETI(ENTITIES_INFORMATIONS), serialiseEntitiesInformationsData(m_scripts.getEntitiesInformations()));
            }
            else
            {
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(CANNOT_CREATE_ENTITY), name));
            }
        }
        break;
        case INJECT_CODE:
        {
            GM_CHECK();
            QString name, code;
            QE(extractInjectCodeData(pa->data, name, code));

            if(!m_scripts.entityExists(name))
            {
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(ENTITY_NOT_FOUND), name));
            }
            else
            {
                bool b=false;
                QString err = m_scripts.pushCode(name, code, &b);
                if(!b)
                {
                    m_network->sendToClient(cID, ETI(SCRIPT_MESSAGE), serialiseScriptMessageData(ETI(ERROR_MSG), name, err));
                    log("Erreur de script (" + name + ") : \"" + err + "\"");
                }
            }
        }
        break;
        case DELETE_ENTITY:
        {
            GM_CHECK();
            QString name;
            QE(extractDeleteEntityData(pa->data, name));
            if(m_scripts.deleteEntity(name))
                m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(ENTITY_NOT_FOUND), name));
            else
                m_network->sendToClient(cID, ETI(DELETE_ENTITY), serialiseDeleteEntityData(name));

        }
        break;
        default:
        {
            log("ERROR : packet type "+QString::number(pa->type)+" unknown ! (from Client "+QString::number(cID)+")");
            m_network->sendToClient(cID, ETI(ERROR), serialiseErrorData(ETI(INVALID_PACKET)));
        }
        break;
    }

   // delete pa;
}
