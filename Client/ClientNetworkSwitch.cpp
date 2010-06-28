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
            qDebug() << "Ping = " << m_ping;
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

            qDebug()<<txt<<can;
            emit chatReceived(sender, txt, can);
        }
        break;
        case NEW_GM:
        {
            CLID gm;
            extractNewGMData(packet->data, gm);
            qDebug()<<gm;
        }
        break;
        case VOTED:
        {
            CLID f, t;
            extractVotedData(packet->data, f, t);
            qDebug()<<f<<" "<<t;
        }
        break;
        default:
        break;
    }
}
