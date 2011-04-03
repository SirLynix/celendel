#include "Server.h"
#include "..\Shared\Serializer.h"

#include <QCoreApplication>
#include <QSettings>

Server::Server(QObject* parent) : QObject(parent)
{
    QCoreApplication::setOrganizationName("Celendel Project");
    QCoreApplication::setOrganizationDomain("http://code.google.com/p/celendel/");
    QCoreApplication::setApplicationName("Celendel");

    QStringList args = QCoreApplication::arguments();
    quint16 port=SERVER_PORT;

    if(args.size()>1)
        port=args[1].toInt();

    m_network=new ServerNetwork(port, this); //Start the network

    connect(m_network, SIGNAL(newClient(CLID)), this, SLOT(addClient(CLID)));
    connect(m_network, SIGNAL(clientGone(CLID)), this, SLOT(removeClient(CLID)));
    connect(m_network, SIGNAL(dataReceived(std::auto_ptr<Packet>, CLID)), this, SLOT(processData(std::auto_ptr<Packet>, CLID)));

    m_gameStarted=false;
    m_GMID=0;
    m_map=new MapInformations();
    serverName="Server";

}

Server::~Server()
{
    for(int i=0; i<m_players.size();++i)
        delete m_players[i];

    delete m_map;
}

/*void Server::processData(Packet* pa, CLID cID)*/
/// Moved in ServerSwitch.cpp

ServerInformations Server::getServerInformations() const
{
    ServerInformations si;
    for(int i=0;i<m_players.size();++i)
    {
        si.players[m_players[i]->ID()].name=m_players[i]->nickname;
        si.players[m_players[i]->ID()].ip=m_network->getClient(m_players[i]->ID())->socket->peerAddress().toString();//Holy sh*t !
    }

    si.gameMasterID=m_GMID;
    si.location=location;
    si.timeOfDay=timeOfDay;
    si.gameStarted=gameStarted();
    si.serverName=serverName;
    si.motd=motd;
    si.narration=narration;
    si.languages=m_translator.getLanguages();
    si.dictionaries=m_translator.getDictionariesList();

    return si;
}

void Server::launchGame()
{
    m_gameStarted=true;
    log("Game have been launched by Game Master !");
    m_network->sendToAll(ETI(GAME_LAUNCHED), QByteArray());
}

void Server::addClient(CLID cID)
{
    m_players.append(new Player(cID));
    log("Player "+QString::number(cID)+" added to game.");
    m_network->sendToClient(cID, ETI(SET_CLID), serialiseSetCLIDData(cID));
    m_network->sendToClient(cID, ETI(SERVER_INFORMATIONS), serialiseServerInformationsData(getServerInformations()));
    m_network->sendToClient(cID, ETI(MAP_INFORMATIONS), serialiseMapInformationsData(*m_map));
    m_network->sendToClient(cID, ETI(UPDATE_RESSOURCES), serialiseUpdateRessourcesData(m_ressources));
    m_network->sendToAll(ETI(CLIENT_JOINED), serialiseClientJoinedData(cID, m_network->getClient(cID)->socket->peerAddress().toString()));
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

void Server::cleanUp()
{
    m_GMID=0;
    m_gameStarted=false;
    for(int i=0; i<m_players.size();++i)
    {
        m_players[i]->reset();
    }
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
            /*if(m_players[i]!=m_players.last()) //Put the pointer to the end of the list, for avoiding empty cases.
            {
                m_players[i]=m_players.last();
            }
            m_players.removeLast();*/
            m_players.removeAt(i);

            if(ply->isGM()&&m_players.size())
                changeGM(m_players[0]->ID());

            if(ply->isGM()&&!m_players.size())
                cleanUp();

            ply->deleteLater();

            m_network->sendToAll(ETI(CLIENT_LEFT), serialiseClientLeftData(cID));
            log("Player succefully removed from game.");
            return;
        }
    }
}
