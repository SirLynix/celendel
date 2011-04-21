#include "Server.h"
#include "../Shared/Serializer.h"

#include <QCoreApplication>
#include <QSettings>
#include <QStringList>


Server::Server(QObject* parent) : QObject(parent)
{
    qRegisterMetaType<QStringPair>("QStringPair");
    qRegisterMetaTypeStreamOperators<QStringPair>("QStringPair");
    qMetaTypeId<QStringPair>();

    qRegisterMetaType<QStringPairList>("QStringPairList");
    qRegisterMetaTypeStreamOperators<QStringPairList>("QStringPairList");
    qMetaTypeId<QStringPairList>();

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

    connect(&m_scripts, SIGNAL(entityRequireUpdate(const QString&)), this, SLOT(sendEntityInfos(const QString&)));

    connect(&m_scripts, SIGNAL(sendGMMsg(QString, QString)), this, SLOT(sendGMMsg(QString, QString)));
    connect(&m_scripts, SIGNAL(sendMsg(QString, QString)), this, SLOT(sendMsg(QString, QString)));
    connect(&m_scripts, SIGNAL(sendPlayerMsg(QString, QString, QString)), this, SLOT(sendPlayerMsg(QString, QString, QString)));
    connect(&m_scripts, SIGNAL(characterListUpdated(const QStringList&)), this, SLOT(updateCharacterList(const QStringList&)));
    connect(&m_scripts, SIGNAL(luaError(QString, QString)), this, SLOT(sendLuaError(QString,QString)));

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
    si.scriptList=getScriptList();

    return si;
}

QList<CLID> Server::getMatchingPlayers(const QString& regexp)
{
    QList<CLID> ret;
    for(int i=0,m=m_players.size();i<m;++i)
        if(m_players[i]->match(regexp))
            ret.append(m_players[i]->ID());

    return ret;
}

void Server::sendLuaError(QString ent, QString m)
{
    m_network->sendToClient(m_GMID, ETI(SCRIPT_MESSAGE), serialiseScriptMessageData(ERROR_MSG, ent, m));
}

void Server::sendGMMsg(QString ent, QString m)
{
    m_network->sendToClient(m_GMID, ETI(SCRIPT_MESSAGE), serialiseScriptMessageData(TO_GM, ent, m));
}

void Server::sendMsg(QString ent, QString m)
{
    m_network->sendToAll(ETI(SCRIPT_MESSAGE), serialiseScriptMessageData(TO_ALL, ent, m));
}

void Server::sendPlayerMsg(QString ent, QString me, QString regexp)
{
    QList<CLID> list = getMatchingPlayers(regexp);
    for(int i=0,m=list.size();i<m;++i)
        m_network->sendToClient(list[i], ETI(SCRIPT_MESSAGE), serialiseScriptMessageData(TO_PLAYER, ent, me));
}

bool Server::mkscriptpath(const QString& scriptName)
{
    if(!isValidScriptName(scriptName))
        return true;

    QString path = SCRIPT_FOLDER+scriptName; path = path.replace('\\', '/');
    path = path.left(path.lastIndexOf('/'));

    return mkpath(path);
}

bool Server::isValidScriptName(const QString& name)
{
    QDir d(SCRIPT_FOLDER+name);

    if(!d.absolutePath().startsWith(QDir::currentPath()+'/'+SCRIPT_FOLDER))
    {
        DEB() << "Permission error : " << d.absolutePath() << '\t' << QDir::currentPath()+'/'+SCRIPT_FOLDER;
        return false;
    }

    return true;
}

void Server::updateCharacterList(const QStringList& c)
{
    m_network->sendToAll(ETI(UPDATE_CHARACTER_LIST), serialiseCharacterListData(c));
}

void Server::sendEntityInfos(const QString& name)
{
    EntityInformations ei = m_scripts.getEntityInformations(name);
    if(ei.name.isEmpty())
        return;

    m_network->sendToAll(ETI(UPDATE_ENTITY_INFORMATIONS), serialiseUpdateEntityInformationsData(ei));
}

QStringList Server::getScriptList()
{
    return listFilesInFolder(SCRIPT_FOLDER, SCRIPT_EXT);
}

void Server::sendScriptList(CLID cID)
{
    m_network->sendToClient(cID, ETI(SCRIPTS_LIST), serialiseScriptListData(getScriptList()));
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
    m_network->sendToClient(cID, ETI(UPDATE_RESSOURCES), serialiseUpdateRessourcesData(m_ressources));
    m_network->sendToClient(cID, ETI(ENTITIES_INFORMATIONS), serialiseEntitiesInformationsData(m_scripts.getEntitiesInformations()));
    m_network->sendToClient(cID, ETI(UPDATE_CHARACTER_LIST), serialiseCharacterListData(m_scripts.getCharacters()));
    m_network->sendToClient(cID, ETI(MAP_INFORMATIONS), serialiseMapInformationsData(*m_map));
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

bool Server::updateScript(const QString& name, const QString& content)
{
    if(!isValidScriptName(name))
        return true;

    mkscriptpath(name);

    QFile file(SCRIPT_FOLDER+name);

    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        return true;

    QTextStream out(&file);
    out<<content;

    return false;
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
