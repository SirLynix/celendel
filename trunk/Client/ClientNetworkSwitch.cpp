#include "ClientNetwork.h"
#include "..\Shared\Serializer.h"
#include <QDebug>

void ClientNetwork::operatePacket(Packet* packet)
{
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
            qDebug() << "Map informations received.";
        }
        break;
        case SERVER_INFORMATIONS:
        {
            ServerInformations si;
            extractServerInformationsData(packet->data, si);

            emit serverInformationsChanged(si);
        }
        break;
        case SET_CLID:
        {
            CLID ID;
            extractSetCLIDData(packet->data, ID);
            emit clientIDChanged(ID);
        }
        break;
        case NEW_NICK:
        {
            CLID nID; QString nick;
            extractNewNickData(packet->data, nID, nick);
            emit nicknameChanged(nID, nick);
        }
        break;
        case CHAT:
        {
            QString txt;
            ENUM_TYPE can;
            CLID sender;
            extractChatData(packet->data, can, txt, sender);

            emit chatReceived(sender, txt, can);
        }
        break;
        case NEW_GM:
        {
            CLID gm;
            extractNewGMData(packet->data, gm);
            emit newGameMaster(gm);
        }
        break;
        case VOTED:
        {
            CLID f, t;
            extractVotedData(packet->data, f, t);
            emit clientVoted(f, t);
        }
        break;
        case ERROR:
        {
            ENUM_TYPE type;
            QString txt;
            extractErrorData(packet->data, type, txt);
            emit error(type, txt);
        }
        break;
        case GTFO_LYNIX:
        {
            CLID tar=0;
            ENUM_TYPE ty=0;
            QString rea;
            extractGTFOLynixData(packet->data, tar, ty, rea);
            emit sanctionned(tar, ty, rea);
        }
        break;
        case ROLL_DICE:
        {
            CLID rID=0;
            quint16 res=0;
            extractDiceRollData(packet->data, rID, res);
            emit diceRolled(rID, res);
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
            extractServerNameData(packet->data, n);
            emit serverName(n);
        }
        case CLIENT_JOINED:
        {
            CLID cID;
            extractClientJoinedData(packet->data, cID);
            emit clientJoined(cID);
        }
        break;
        case CLIENT_LEFT:
        {
            CLID cID;
            extractClientLeftData(packet->data, cID);
            emit clientLeft(cID);
        }
        break;
        case MOTD:
        {
            QString n;
            extractMOTDData(packet->data, n);
            emit motdChanged(n);
        }
        break;
        case ALL_NARRATION:
        {
            QString n;
            extractAllNarrationData(packet->data, n);
            emit narrationChanged(n);
        }
        break;
        default:
        break;
    }
}
