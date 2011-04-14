#include "ClientNetwork.h"
#include "..\Shared\Serializer.h"
#include <QDebug>
#define QE(a) if(a) {emit packetCorrupted(); send(ETI(ERROR), serialiseErrorData(ETI(INVALID_PACKET)));return;}

void ClientNetwork::operatePacket(Packet* packet)
{
    QE(packet==NULL);
    QE(packet->error());
    switch(packet->type)
    {
        case PING:
        {
            m_ping=getTimeStamp()-packet->timestamp;
            emit pingUpdated(m_ping);
        }
        break;
        case MAP_INFORMATIONS:
        {
            MapPtr map (new MapInformations());

            QE(extractMapInformationsData(packet->data, *map));

            if(!map->isValid())
                map.reset(NULL);

            DEB() << "Map changed !";
            emit mapChanged(map);
        }
        break;
        case UPDATE_RESSOURCES:
        {
            QMap<QString, RSID> rss;

            QE(extractUpdateRessourcesData(packet->data, rss));

            DEB() << "Ressources updated";
            emit ressourcesUpdated(rss);
        }
        break;
        case SERVER_INFORMATIONS:
        {
            ServerInformations si;
            QE(extractServerInformationsData(packet->data, si));

            emit serverInformationsChanged(si);
        }
        break;
        case SET_CLID:
        {
            CLID ID;
            QE(extractSetCLIDData(packet->data, ID));
            emit clientIDChanged(ID);
        }
        break;
        case NEW_NICK:
        {
            CLID nID; QString nick;
            QE(extractNewNickData(packet->data, nID, nick));
            emit nicknameChanged(nID, nick);
        }
        break;
        case CHAT:
        {
            QString txt; QString lang;
            ENUM_TYPE can;
            CLID sender;
            QE(extractChatData(packet->data, can, lang, txt, sender));

            emit chatReceived(sender, lang, txt, can);
        }
        break;
        case NEW_GM:
        {
            CLID gm;
            QE(extractNewGMData(packet->data, gm));
            emit newGameMaster(gm);
        }
        break;
        case VOTED:
        {
            CLID f, t;
            QE(extractVotedData(packet->data, f, t));
            emit clientVoted(f, t);
        }
        break;
        case ERROR:
        {
            ENUM_TYPE type;
            QString txt;
            QE(extractErrorData(packet->data, type, txt));
            emit error(type, txt);
        }
        break;
        case GTFO_LYNIX:
        {
            CLID tar=0;
            ENUM_TYPE ty=0;
            QString rea;
            QE(extractGTFOLynixData(packet->data, tar, ty, rea));
            emit sanctionned(tar, ty, rea);
        }
        break;
        case ROLL_DICE:
        {
            CLID rID=0;
            quint16 res=0, max=0;
            QE(extractDiceRollData(packet->data, rID, res, max));
            emit diceRolled(rID, res, max);
        }
        break;
        case GAME_LAUNCHED:
        {
            emit gameLaunched();
        }
        break;
        case SERVER_NAME:
        {
            QString n;
            QE(extractServerNameData(packet->data, n));
            emit serverName(n);
        }
        case CLIENT_JOINED:
        {
            CLID cID; QString IP;
            QE(extractClientJoinedData(packet->data, cID, IP));
            emit clientJoined(cID, IP);
        }
        break;
        case CLIENT_LEFT:
        {
            CLID cID;
            QE(extractClientLeftData(packet->data, cID));
            emit clientLeft(cID);
        }
        break;
        case MOTD:
        {
            QString n;
            QE(extractMOTDData(packet->data, n));
            emit motdChanged(n);
        }
        break;
        case ALL_NARRATION:
        {
            QString n;
            QE(extractAllNarrationData(packet->data, n));
            emit narrationChanged(n);
        }
        break;
        case PLAY_SOUND:
        {
            QString sound; QString lib;
            QE(extractPlaySoundData(packet->data, lib, sound));
            emit playSound(lib, sound);
        }
        break;
        case SYNC_LIBS:
        {
            QList<SoundLibInformations> l;
            QE(extractSyncLibsData(packet->data, l));
            emit syncLibs(l);
        }
        break;
        case LANGUAGES_LIST:
        {
            QList<QPair<QString, QString> > l;
            QE(extractLanguagesData(packet->data, l));
            emit syncLanguagesList(l);
        }
        break;
        case DICO_LIST:
        {
            QStringList l;
            QE(extractDicoListData(packet->data, l));
            emit syncDictionariesList(l);
        }
        break;
        case SCRIPTS_LIST:
        {
            QStringList l;
            QE(extractScriptListData(packet->data, l));
            emit syncScriptList(l);
        }
        break;
        case SEND_SCRIPT:
        {
            QString name, content;
            QE(extractSendScriptData(packet->data, name, content));
            emit scriptReceived(name, content);
        }
        break;
        case ENTITIES_INFORMATIONS:
        {
            QList<EntityInformations> list;
            QE(extractEntitiesInformationsData(packet->data, list));
            emit updateEntities(list);
        }
        break;
        case UPDATE_ENTITY_INFORMATIONS:
        {
            EntityInformations ent;
            QE(extractUpdateEntityInformationsData(packet->data, ent));
            emit updateEntity(ent);
        }
        break;
        case SCRIPT_MESSAGE:
        {
            qint32 t = 0;
            QString ent, txt;
            QE(extractScriptMessageData(packet->data, t, ent, txt));
            switch (t)
            {
                case TO_GM:
                {
                    emit scriptToGMMsg(ent, txt);
                }
                break;
                case TO_OWNER:
                {
                    emit scriptToOwnerMsg(ent, txt);
                }
                break;
                case ACTION_TO_DO:
                {
                    emit scriptActionMsg(ent, txt);
                }
                break;
                case TO_PLAYER:
                {
                    emit scriptToPlayerMsg(ent, txt);
                }
                break;
                case TO_ALL:
                {
                    emit scriptMsg(ent, txt);
                }
                break;
                case ERROR_MSG:
                {
                    emit scriptError(ent, txt);
                }
                break;
                default:
                break;
            }

        }
        break;
        case DELETE_ENTITY:
        {
            QString ent;
            QE(extractDeleteEntityData(packet->data, ent));
            emit entityDeleted(ent);
        }
        break;
        case UPDATE_CHARACTER_LIST:
        {
            QStringList list;
            QE(extractCharacterListData(packet->data, list));

            emit updateCharacterList(list);
        }
        break;
        default:
        break;
    }
}
