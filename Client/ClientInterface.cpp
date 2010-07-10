#include "ClientInterface.h"
#include "..\Shared\Serializer.h"
#include <QTime>

ClientInterface::ClientInterface()
{
    m_mapWi=new QWidget(this); ///Debug
    m_mapWi->setMinimumSize(200,200);

    setCentralWidget(m_mapWi);

    #include "GUI.cpp"

    m_ID=0;
    m_gameStarted=false;

    m_network=new ClientNetwork(this);
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

    setTitle("");
    updateGMLabel();
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

void ClientInterface::setTitle(const QString& serverName)
{
    if(serverName.isEmpty())
    {
        setWindowTitle(tr("Celendel - Déconnecté"));
        return;
    }

    setWindowTitle(tr("Celendel - %1", "Window title").arg(serverName));
}

void ClientInterface::connectionEtablished()
{
    lg(tr("Vous êtes maintenant connecté à un serveur (%1:%2) !").arg(m_network->serverIP()).arg(m_network->serverPort()));
}

void ClientInterface::connectionLost()
{
    lg(tr("Vous avez été déconnecté du serveur. Tappez /retry pour tenter une reconnexion."));
    setTitle("");
    m_nickMap.clear();
    updatePlayerList();
}

void ClientInterface::clientJoined(CLID cID)
{
    if(cID==m_ID)
        return;

    lg(tr("Un joueur s'est connecté (ID %1).").arg(cID));
    m_nickMap.insert(cID, "");
    updatePlayerList();
}

void ClientInterface::clientLeft(CLID cID)
{
    lg(tr("%1 s'est déconnecté.").arg(anonym(cID)));
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
    setTitle(n);
}

void ClientInterface::updatePlayerList()
{
    m_playerList->clear();
    QMap<CLID, QString>::const_iterator i = m_nickMap.constBegin();
    while (i != m_nickMap.constEnd())
    {
        QStandardItem *item = new QStandardItem(anonym2(i.key()));
        m_playerList->appendRow(item);

        item->appendRow(new QStandardItem(tr("Client ID %1").arg(i.key())));
        if(i.key()==m_GMID)
        {
            item->appendRow(new QStandardItem(tr("Maître du Jeu")));
        }
        else
            item->appendRow(new QStandardItem(tr("Simple joueur")));

        if(m_gameStarted)
        {
            QStandardItem *it = new QStandardItem(tr("Rôle :"));
            item->appendRow(it);
            it->appendRow(new QStandardItem(getRolePlayName(i.key())));
        }

        ++i;
    }
}

void ClientInterface::updateGMLabel()
{
    if(m_GMID==0)
    {
        m_GMLabel->setText(tr("<strong>Il n'y a pas de Maître du Jeu.</strong>"));
    }
    else if(m_GMID==m_ID)
    {
        m_GMLabel->setText(tr("<strong>Vous êtes actuellement le Maître du Jeu.</strong>"));
    }
    else
    {
        m_GMLabel->setText(tr("Le Maître du jeu est <strong>%1</strong>").arg(anonym2(m_GMID)));
    }
}

void ClientInterface::sanctionned(CLID ID, ENUM_TYPE type, QString reason)
{
    QString st;
    if(type==KICK)
    {
        st=tr("a été éjecté");
    }
    else
        st=tr("a été banni");

    QString rea;
    if(!reason.isEmpty())
    {
        rea=" "+tr("Raison : %1").arg(reason);
    }

    lg(tr("%1 %2 du serveur par le Maître du Jeu.%3").arg(anonym(ID)).arg(st).arg(rea));
}

void ClientInterface::gameLaunched()
{
    lg(tr("La partie a été lancée par le <strong>Maître du Jeu !</strong>"), true, true);
}

void ClientInterface::showError(ENUM_TYPE e, QString txt)
{
    lg(tr("Erreur : %1").arg(ETS(e, txt)));
}

void ClientInterface::changeClientID(CLID ID)
{
    m_ID=ID;
    lg(tr("Votre Client ID est le %1.").arg(m_ID));
}

void ClientInterface::clientVoted(CLID f, CLID t)
{
    if(f==t)
    {
        lg(tr("%1 a voté pour lui-même pour le poste de <strong>Maître de Jeu</strong>.").arg(anonym(f)), true, true);
    }
    else
        lg(tr("%1 a voté pour %2 pour le poste de <strong>Maître de Jeu</strong>.").arg(anonym(f)).arg(anonym(t)), true, true);
    if(m_nickMap.value(t)=="Lynix")
        lg(tr("Evidement, comme c'est un vote pour Lynix, il ne comptera <strong>pas</strong>. Faut pas rêver !"), false, true);
}

void ClientInterface::changeGameMaster(CLID ID)
{
    m_GMID=ID;
    lg(tr("<em><strong>%1</strong> est maintenant <strong>Maître du Jeu</strong>.</em>").arg(anonym(ID)), true, true);
    updatePlayerList();
    updateGMLabel();
}

void ClientInterface::changeServerInformations(ServerInformations si)
{

    lg(tr("<strong>Mise à jour des informations du serveur :</strong>"));

    if(!si.serverName.isEmpty()&&m_serverName!=si.serverName)
    {
        m_serverName=si.serverName;
        lg(tr("Nom du serveur : %1").arg(m_serverName), false, true);
        setTitle(m_serverName);
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
        lg(tr("<em>Vous êtes le seul client connecté.</em>"), false, true);
    }
    else
    {
        lg(tr("<strong>%n</strong> client(s) maintenant connecté(s).","",nms), false, true);
    }

    if(m_GMID!=si.gameMasterID && si.gameMasterID!=0)
    {
        m_GMID=si.gameMasterID;
        lg(tr("<em><strong>%1</strong> est <strong>Maître du Jeu</strong></em>").arg(anonym(m_GMID)), false, true);
        updateGMLabel();
    }

    if(si.gameStarted)
    {
        if(m_gameStarted!=si.gameStarted)
        {
            m_gameStarted=si.gameStarted;
            lg(tr("<em>La partie a déjà démarré.</em>"), false, true);
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
