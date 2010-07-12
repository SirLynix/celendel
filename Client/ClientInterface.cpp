#include "ClientInterface.h"
#include "..\Shared\Serializer.h"
#include <QTime>

ClientInterface::ClientInterface()
{

    #include "GUI.cpp"

    QSettings* set=allocateSettings();

    m_network=new ClientNetwork(set->value(PARAM_IP, SERVER_IP).toString(), set->value(PARAM_PORT, SERVER_PORT).toInt(), this);
    connect(m_network, SIGNAL(chatReceived(CLID, QString, ENUM_TYPE)), this, SLOT(chat(CLID, QString, ENUM_TYPE )));
    connect(m_network, SIGNAL(serverInformationsChanged(ServerInformations)), this, SLOT(changeServerInformations(ServerInformations)));
    connect(m_network, SIGNAL(clientIDChanged(CLID)), this, SLOT(changeClientID(CLID)));
    connect(m_network, SIGNAL(nicknameChanged(CLID, QString)), this, SLOT(changeClientNickname(CLID, QString)));
    connect(m_network, SIGNAL(error(ENUM_TYPE, QString)), this, SLOT(showError(ENUM_TYPE, QString)));
    connect(m_network, SIGNAL(newGameMaster(CLID)), this, SLOT(changeGameMaster(CLID)));
    connect(m_network, SIGNAL(clientVoted(CLID, CLID)), this, SLOT(clientVoted(CLID, CLID)));
    connect(m_network, SIGNAL(connectionEtablished()), this, SLOT(connectionEtablished()));
    connect(m_network, SIGNAL(connectionLost()), this, SLOT(connectionLost()));
    connect(m_network, SIGNAL(sanctionned(CLID, ENUM_TYPE, QString)), this, SLOT(sanctionned(CLID, ENUM_TYPE, QString)));
    connect(m_network, SIGNAL(diceRolled(CLID, quint16)), this, SLOT(diceRolled(CLID, quint16)));
    connect(m_network, SIGNAL(gameLaunched()), this, SLOT(gameLaunched()));
    connect(m_network, SIGNAL(serverName(QString)), this, SLOT(serverName(QString)));
    connect(m_network, SIGNAL(clientLeft(CLID)), this, SLOT(clientLeft(CLID)));
    connect(m_network, SIGNAL(clientJoined(CLID)), this, SLOT(clientJoined(CLID)));

    resetData();

    setCSS(set->value(PARAM_CSS).toString());
    setInterface(set->value(PARAM_INTERFACE, DEFAULT_INTERFACE).toString());

    delete set;
}

void ClientInterface::setInterface(const QString& path)
{
    QFile file (path);
    if (!file.open(QIODevice::ReadOnly))
        return;

    restoreState(file.readAll());
}

void ClientInterface::playerListMenu(const QPoint& pos)
{
    QModelIndex mod = m_v_pl->indexAt(pos);
    if(!mod.isValid())
        return;
    CLID cID=mod.data(DTA_CLID).toInt();
    QList<QAction*> list;

    m_kick->setData(cID);
    m_ban->setData(cID);
    m_voteGM->setData(cID);
    m_changeGM->setData(cID);

    if(isGM())
        list << m_kick << m_ban << m_changeGM;

    if(m_GMID==0&&!m_voted) //No GM
        list << m_voteGM;

    if(!list.isEmpty())
        QMenu::exec(list, mapToGlobal(pos));
}

void ClientInterface::actionKick()
{
    CLID cID=m_kick->data().toInt();
    if(cID==0)
        return;

    m_network->send(ETI(GTFO_LYNIX), serialiseGTFOLynixData(cID, ETI(KICK)));
}

void ClientInterface::actionVoteGM()
{
    CLID cID=m_voteGM->data().toInt();
    if(cID==0)
        return;

    m_network->send(ETI(GM_ELECT), serialiseGMElectData(cID));
}

void ClientInterface::actionChangeGM()
{
    CLID cID=m_changeGM->data().toInt();
    if(cID==0)
        return;

    m_network->send(ETI(NEW_GM), serialiseGMElectData(cID));
}

void ClientInterface::actionBan()
{
    CLID cID=m_ban->data().toInt();
    if(cID==0)
        return;

    m_network->send(ETI(GTFO_LYNIX), serialiseGTFOLynixData(cID, ETI(BAN)));
}

void ClientInterface::lg(const QString txt, bool time, bool html)
{
    QString tmp;
    if(time)
    {
        tmp = QTime::currentTime().toString("HH:mm:ss") + " : ";
    }
    tmp+=txt;

    if(html)
    {
        m_chat->setHtml(m_chat->toHtml()+tmp);
        m_chat->verticalScrollBar()->setValue(m_chat->verticalScrollBar()->maximum());
    }
    else
        m_chat->append(tmp.toAscii());
}

void ClientInterface::switchConnectionState()
{
    if(!isConnected())
    {
        m_network->connection();
    }
    else
    {
        m_network->disconnection();
    }
}
void ClientInterface::openSettings()
{
    ClientSettings cs(this);
    cs.exec();
    QSettings* set=allocateSettings();

    m_network->setServer(set->value(PARAM_IP).toString(), set->value(PARAM_PORT).toInt());
    m_network->send(ETI(SET_NICK), serialiseSetNickData(set->value(PARAM_NICK).toString()));

    delete set;
}

void ClientInterface::setTitle()
{
    if(!isConnected())
    {
        setWindowTitle(tr("Celendel - D�connect�"));
        return;
    }
    if(!m_serverName.isEmpty())
    {
        setWindowTitle(tr("Celendel - %1", "Window title").arg(m_serverName));
        return;
    }
    setWindowTitle(tr("Celendel - Connect�", "Window title"));
}

void ClientInterface::connectionEtablished()
{
    QSettings* set=allocateSettings();

    lg(tr("Vous �tes maintenant <strong>connect�</strong> � un serveur (%1:%2) !").arg(m_network->serverIP()).arg(m_network->serverPort()), true, true);
    m_network->send(ETI(SET_NICK), serialiseSetNickData(set->value(PARAM_NICK).toString()));
    m_ac_joinOrLeave->setText(tr("&Se d�connecter du serveur"));
    updateGMLabel();

    delete set;
}

void ClientInterface::connectionLost()
{
    lg(tr("Vous avez �t� d�connect� du serveur. Tappez /retry pour tenter une reconnexion."));
    m_ac_joinOrLeave->setText(tr("&Se connecter au serveur"));
    resetData();
}

void ClientInterface::resetData()
{
    setTitle();
    m_gameStarted=false;
    m_voted=false;
    m_ID=0;
    m_GMID=0;
    m_location.clear();
    m_TOD.clear();
    m_serverName.clear();
    m_nickMap.clear();
    updatePlayerList();
    updateGMLabel();
}

void ClientInterface::clientJoined(CLID cID)
{
    if(cID==m_ID)
        return;

    lg(tr("Un joueur s'est connect� (ID %1).").arg(cID));
    m_nickMap.insert(cID, "");
    updatePlayerList();
}

void ClientInterface::clientLeft(CLID cID)
{
    lg(tr("%1 s'est d�connect�.").arg(anonym(cID)));
    m_nickMap.remove(cID);
    updatePlayerList();
}

void ClientInterface::diceRolled(CLID ID, quint16 result)
{
    lg(tr("%1 lance 1d20, et obtient un %2.").arg(anonym(ID)).arg(result));
}

void ClientInterface::rollDice()
{
    m_network->send(ETI(ROLL_DICE), serialiseDiceRollData(0,0) );
}

void ClientInterface::changeClientNickname(CLID ID, QString nick)
{
    QString old(anonym(ID));
    m_nickMap[ID]=nick;
    lg(tr("%1 s'appelle maintenant %2.").arg(old).arg(nick));
    updatePlayerList();
}

void ClientInterface::serverName(QString n)
{
    m_serverName=n;
    lg(tr("Le serveur s'appelle maintenant \"%1\".").arg(n));
    setTitle();
}

void ClientInterface::setCSS(const QString& fileName)
{
    if(fileName.isEmpty())
    {
        setStyleSheet(QString());
        return;
    }

    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString css=file.readAll();
    if(css.isEmpty())
        return;

    setStyleSheet(css);
}

void ClientInterface::updatePlayerList()
{
    m_playerList->clear();
    if(!m_network->isConnected())
        return;

    QMap<CLID, QString>::const_iterator i = m_nickMap.constBegin();
    while (i != m_nickMap.constEnd())
    {
        QStandardItem *item = new QStandardItem(anonym2(i.key()));
        item->setData(i.key(), DTA_CLID);
        m_playerList->appendRow(item);

        {
        QStandardItem *u=new QStandardItem(tr("Client ID %1").arg(i.key()));
        u->setData(i.key(), DTA_CLID);
        item->appendRow(u);
        }
        {
        QStandardItem *sti=new QStandardItem;
        sti->setData(i.key(), DTA_CLID);
        if(i.key()==m_GMID)
        {
            sti->setText(tr("Ma�tre du Jeu"));
        }
        else
            sti->setText(tr("Simple joueur"));

        item->appendRow(sti);
        }

        if(m_gameStarted)
        {
            QStandardItem *it = new QStandardItem(tr("R�le :"));
            it->setData(i.key(), DTA_CLID);
            item->appendRow(it);
            QStandardItem* u=new QStandardItem(getRolePlayName(i.key()));
            u->setData(i.key(), DTA_CLID);
            it->appendRow(u);
        }

        ++i;
    }
}

void ClientInterface::updateGMLabel()
{
    if(!m_network->isConnected())
    {
        m_GMLabel->setText(tr("Vous n'�tes pas connect�."));
    }
    else if(m_GMID==0)
    {
        m_GMLabel->setText(tr("<strong>Il n'y a actuellement pas de Ma�tre du Jeu.</strong>"));
    }
    else if(m_GMID==m_ID)
    {
        m_GMLabel->setText(tr("<strong>Vous �tes actuellement le Ma�tre du Jeu.</strong>"));
    }
    else
    {
        m_GMLabel->setText(tr("Le Ma�tre du jeu est <strong>%1</strong>").arg(anonym2(m_GMID)));
    }
}

void ClientInterface::sanctionned(CLID ID, ENUM_TYPE type, QString reason)
{
    QString st;
    if(type==KICK)
    {
        st=tr("a �t� �ject�");
    }
    else
        st=tr("a �t� banni");

    QString rea;
    if(!reason.isEmpty())
    {
        rea=" "+tr("Raison : %1").arg(reason);
    }

    lg(tr("%1 %2 du serveur par le Ma�tre du Jeu.%3").arg(anonym(ID)).arg(st).arg(rea));
}

void ClientInterface::gameLaunched()
{
    lg(tr("La partie a �t� lanc�e par le <strong>Ma�tre du Jeu !</strong>"), true, true);
}

void ClientInterface::showError(ENUM_TYPE e, QString txt)
{
    lg(tr("Erreur : \"%1\"").arg(ETS(e, txt)));
}

void ClientInterface::changeClientID(CLID ID)
{
    m_ID=ID;
    lg(tr("Votre Client ID est le %1.").arg(m_ID));
}

void ClientInterface::clientVoted(CLID f, CLID t)
{
    if(f==m_ID)
        m_voted=true;

    if(f==t)
    {
        lg(tr("%1 a vot� pour lui-m�me pour le poste de <strong>Ma�tre de Jeu</strong>.").arg(anonym(f)), true, true);
    }
    else
        lg(tr("%1 a vot� pour %2 pour le poste de <strong>Ma�tre de Jeu</strong>.").arg(anonym(f)).arg(anonym(t)), true, true);
    if(m_nickMap.value(t)=="Lynix")
        lg(tr("Evidement, comme c'est un vote pour Lynix, il ne comptera <strong>pas</strong>. Faut pas r�ver !"), false, true);
}

void ClientInterface::changeGameMaster(CLID ID)
{
    m_GMID=ID;
    lg(tr("<em><strong>%1</strong> est maintenant <strong>Ma�tre du Jeu</strong>.</em>").arg(anonym(ID)), true, true);
    updatePlayerList();
    updateGMLabel();
}

void ClientInterface::changeServerInformations(ServerInformations si)
{

    lg(tr("<strong>Mise � jour des informations du serveur :</strong>"));

    if(!si.serverName.isEmpty()&&m_serverName!=si.serverName)
    {
        m_serverName=si.serverName;
        lg(tr("Nom du serveur : %1").arg(m_serverName), false, true);
        setTitle();
    }

    int nms=si.playersName.size();

    m_nickMap.clear();
    QMap<CLID, QString>::const_iterator i = si.playersName.constBegin(); //Manual copy - operator=() seems to be broken for empty values like QString("")... I realy don't know why (Gigotdarnaud, 2 July 2010)
    while (i != si.playersName.constEnd())
    {
        m_nickMap.insert(i.key(),i.value());
        ++i;
    }



    if(nms==1)
    {
        lg(tr("<em>Vous �tes le seul client connect�.</em>"), false, true);
    }
    else
    {
        lg(tr("<strong>%n</strong> client(s) maintenant connect�(s).","",nms), false, true);
    }

    if(m_GMID!=si.gameMasterID && si.gameMasterID!=0)
    {
        m_GMID=si.gameMasterID;
        lg(tr("<em><strong>%1</strong> est <strong>Ma�tre du Jeu</strong></em>").arg(anonym(m_GMID)), false, true);
        updateGMLabel();
    }

    if(si.gameStarted)
    {
        if(m_gameStarted!=si.gameStarted)
        {
            m_gameStarted=si.gameStarted;
            lg(tr("<em>La partie a d�j� d�marr�.</em>"), false, true);
        }
        if(si.location!=m_location && !m_location.isEmpty())
        {
            m_location=si.location;
            lg(tr("<em>Lieu du RP</em> : %1").arg(m_location), false, true);
        }
        if(si.timeOfDay!=m_TOD && !m_TOD.isEmpty())
        {
            m_TOD=si.timeOfDay;
            lg(tr("<em>Heure du RP :</em> %1").arg(m_TOD), false, true);
        }
    }
    updatePlayerList();
}

QString ClientInterface::anonym2(CLID ID)
{
    QString nick=m_nickMap.value(ID);

    if(nick.isEmpty())
        return tr("Client anonyme %1").arg(ID);

    return nick;
}

QString ClientInterface::anonym(CLID ID)
{
    QString nick=m_nickMap.value(ID);

    if(nick.isEmpty())
        return tr("Le client anonyme [%1]").arg(ID);

    if(m_GMID == ID)
        return tr("(MJ) %1[%2]").arg(nick).arg(ID);

    return tr("%1[%2]").arg(nick).arg(ID);
}

QString ClientInterface::getRolePlayName(CLID ID)
{
    ///DEBUG
    return m_nickMap.value(ID);
}

void ClientInterface::chat(CLID sender, QString txt, ENUM_TYPE canal)
{
    if(canal==NORMAL)
    {
        lg(anonym(sender)+" : "+txt);
    }
    else if(canal==NARRATOR)
    {
        m_narrator->append(txt);
        m_RPChat->append(txt);
    }
    else if(canal==RP)
    {
        m_RPChat->append(getRolePlayName(sender) + " : " + txt);
    }
    else if(canal==SELF_NARRATOR)
    {
        m_RPChat->append(getRolePlayName(sender) + " " + txt);
        m_narrator->append(getRolePlayName(sender) + " " + txt);
    }
}