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
            qDebug() << "Map informations received.";
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
            quint16 res=0;
            QE(extractDiceRollData(packet->data, rID, res));
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
        default:
        break;
    }
}
