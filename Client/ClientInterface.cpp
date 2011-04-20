#include "ClientInterface.h"
#include "..\Shared\Serializer.h"
#include <QTime>

#include "AboutWindow.h"
#include "SoundManager.h"
#include "SoundsGUI.h"
#include "VOIP/VOIP.h"
#include "MapEditor.h"
#include "ScriptManager.h"
#include "EntitiesManager.h"
#include "CharactersManager.h"


ClientInterface::ClientInterface()
{
    qRegisterMetaType<QStringPair>("QStringPair");
    qRegisterMetaTypeStreamOperators<QStringPair>("QStringPair");
    qMetaTypeId<QStringPair>();

    qRegisterMetaType<QStringPairList>("QStringPairList");
    qRegisterMetaTypeStreamOperators<QStringPairList>("QStringPairList");
    qMetaTypeId<QStringPairList>();

    m_mapEditor=NULL;
    m_mapWi=new MapWidget(this);

    buildGUI();

    QSettings* set=NULL;
    set=allocateSettings();

    QStringList args = QCoreApplication::arguments();

    quint16 port=0; port=set->value(PARAM_PORT, SERVER_PORT).toInt();
    QString IP(set->value(PARAM_IP, SERVER_IP).toString());

    if(args.size()>1)
    {
        QStringList spl=args[1].split(':',QString::SkipEmptyParts);

        QRegExp ex("\\b(?:\\d{1,3}\\.){3}\\d{1,3}\\b");
        if(ex.exactMatch(spl[0]))
        {
            IP=spl[0];
            if(spl.size()>1)
            {
                quint16 p=spl[1].toInt();
                if(p<1024)
                {
                    qDebug() << "Error invalid port";
                }
                else
                    port=p;
            }
        }
        else
            qDebug() << "Error invalid args";
    }


    m_network=new ClientNetwork(IP, port, this);
    connect(m_network, SIGNAL(chatReceived(CLID, QString, QString, ENUM_TYPE)), this, SLOT(chat(CLID, QString, QString, ENUM_TYPE )));
    connect(m_network, SIGNAL(serverInformationsChanged(ServerInformations)), this, SLOT(changeServerInformations(ServerInformations)));
    connect(m_network, SIGNAL(clientIDChanged(CLID)), this, SLOT(changeClientID(CLID)));
    connect(m_network, SIGNAL(nicknameChanged(CLID, QString)), this, SLOT(changeClientNickname(CLID, QString)));
    connect(m_network, SIGNAL(error(ENUM_TYPE, QString)), this, SLOT(showError(ENUM_TYPE, QString)));
    connect(m_network, SIGNAL(newGameMaster(CLID)), this, SLOT(changeGameMaster(CLID)));
    connect(m_network, SIGNAL(clientVoted(CLID, CLID)), this, SLOT(clientVoted(CLID, CLID)));
    connect(m_network, SIGNAL(connectionEtablished()), this, SLOT(connectionEtablished()));
    connect(m_network, SIGNAL(connectionLost()), this, SLOT(connectionLost()));
    connect(m_network, SIGNAL(sanctionned(CLID, ENUM_TYPE, QString)), this, SLOT(sanctionned(CLID, ENUM_TYPE, QString)));
    connect(m_network, SIGNAL(diceRolled(CLID, quint16, quint16)), this, SLOT(diceRolled(CLID, quint16, quint16)));
    connect(m_network, SIGNAL(gameLaunched()), this, SLOT(gameLaunched()));
    connect(m_network, SIGNAL(serverName(QString)), this, SLOT(serverName(QString)));
    connect(m_network, SIGNAL(motdChanged(QString)), this, SLOT(motdChanged(QString)));
    connect(m_network, SIGNAL(clientLeft(CLID)), this, SLOT(clientLeft(CLID)));
    connect(m_network, SIGNAL(clientJoined(CLID, QString)), this, SLOT(clientJoined(CLID, QString)));
    connect(m_network, SIGNAL(narrationChanged(QString)), this, SLOT(narrationChanged(QString)));
    connect(m_network, SIGNAL(playSound(QString, QString)), this, SLOT(playSound(QString, QString)));
    connect(m_network, SIGNAL(syncLibs(QList<SoundLibInformations>)), this, SLOT(syncSoundLibs(QList<SoundLibInformations>)));
    connect(m_network, SIGNAL(syncLanguagesList(QList<QPair<QString, QString> >)), this, SLOT(syncLanguagesList(QList<QPair<QString, QString> >)));
    connect(m_network, SIGNAL(syncDictionariesList(QStringList)), this, SLOT(syncDictionariesList(QStringList)));
    connect(m_network, SIGNAL(syncScriptList(QStringList)), m_scriptManager, SLOT(updateScriptList(QStringList)));
    connect(m_network, SIGNAL(mapChanged(MapPtr)), m_mapWi, SLOT(setMap(MapPtr)));
    connect(m_network, SIGNAL(ressourcesUpdated(const QMap<QString, RSID>&)), m_mapWi, SLOT(updateRessources(const QMap<QString, RSID>&)));
    connect(m_network, SIGNAL(scriptReceived(QString,QString)), m_scriptManager, SLOT(showScriptText(QString,QString)));
    connect(m_scriptManager, SIGNAL(requestScriptDownload(QString)), this, SLOT(requestScriptDownload(QString)));
    connect(m_scriptManager, SIGNAL(sendScriptToServer(QString,QString)), this, SLOT(sendScriptToServer(QString,QString)));
    connect(m_scriptManager, SIGNAL(renameScript(QString,QString)), this, SLOT(renameScript(QString,QString)));
    connect(m_scriptManager, SIGNAL(deleteScript(QString)), this, SLOT(deleteScript(QString)));
    connect(m_scriptManager, SIGNAL(makeEntity(QString,QString)), this, SLOT(makeEntity(QString,QString)));
    connect(m_network, SIGNAL(entityDeleted(QString)), m_entitiesManager, SLOT(entityDeleted(QString)));
    connect(m_network, SIGNAL(updateEntities(const QList<EntityInformations>&)), m_entitiesManager, SLOT(setEntities(const QList<EntityInformations>&)));
    connect(m_network, SIGNAL(updateEntity(const EntityInformations&)), m_entitiesManager, SLOT(updateEntity(const EntityInformations&)));
    connect(m_entitiesManager, SIGNAL(injectCode(QString,QString)), this, SLOT(injectCode(QString,QString)));
    connect(m_entitiesManager, SIGNAL(deleteEntity(QString)), this, SLOT(deleteEntity(QString)));
    connect(m_network, SIGNAL(scriptToGMMsg(QString,QString)), this, SLOT(scriptToGMMsg(QString,QString)));
    connect(m_network, SIGNAL(scriptToOwnerMsg(QString,QString)), this, SLOT(scriptToOwnerMsg(QString,QString)));
    connect(m_network, SIGNAL(scriptActionMsg(QString,QString)), this, SLOT(scriptActionMsg(QString,QString)));
    connect(m_network, SIGNAL(scriptToPlayerMsg(QString,QString)), this, SLOT(scriptToPlayerMsg(QString,QString)));
    connect(m_network, SIGNAL(scriptMsg(QString,QString)), this, SLOT(scriptMsg(QString,QString)));
    connect(m_network, SIGNAL(scriptError(QString,QString)), this, SLOT(scriptError(QString,QString)));
    connect(m_network, SIGNAL(updateCharacterList(const QStringList&)), m_characterMngr, SLOT(updateCharacterList(const QStringList&)));

    getVOIP().setEnabled(set->value(PARAM_VOIP_ENABLED, true).toBool());
    getVOIP().setVolume(set->value(PARAM_VOIP_SOUND, 100.f).toFloat());
    getVOIP().setQuality(set->value(PARAM_VOIP_QUALITY, 4).toFloat());
    connect(&getVOIP(), SIGNAL(dataPerSecond(int, int)), this, SLOT(dataPerSecond(int, int)));

    resetData();

    setCSS(set->value(PARAM_CSS).toString());
    setInterface(set->value(PARAM_INTERFACE, DEFAULT_INTERFACE).toString());
    sndMngr.setVolume(set->value(PARAM_SOUND, 100.f).toFloat());

    sndMngr.setLibList(set->value(PARAM_SOUNDLIBS, QStringList()).toStringList());

    buildGMStuff();
    updateGMPanel();

    delete set;
}

void ClientInterface::dataPerSecond(int d, int u)
{
    if(d<1024)
        m_dlPerSec->setText(tr("Download : %1 o/s").arg(d,5));
    else if(d<1024*1024)
        m_dlPerSec->setText(tr("Download : %1 kio/s").arg((double)d/1024,5,'g',2));
    else
        m_dlPerSec->setText(tr("Download : %1 mio/s").arg((double)d/1024/1024,5,'g',2));

    if(u<1024)
        m_upPerSec->setText(tr("Upload : %1 o/s", "").arg(u,5));
    else if(u<1024*1024)
        m_upPerSec->setText(tr("Upload : %1 kio/s").arg((double)u/1024,5,'g',2));
    else
        m_upPerSec->setText(tr("Upload : %1 mio/s").arg((double)u/1024/1024,5,'g',2));
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

    if(!m_playersMap.contains(cID))
        return;

    QList<QAction*> list;

    m_kick->setData(cID);
    m_ban->setData(cID);
    m_voteGM->setData(cID);
    m_changeGM->setData(cID);
    m_VOIPDisconnect->setData(cID);
    m_VOIPConnect->setData(cID);
    m_VOIPVolume->setData(cID);

    if(isGM()&&cID!=m_ID)
        list << m_kick << m_ban << m_changeGM;

    if(m_GMID==0&&!m_voted) //No GM
        list << m_voteGM;

    if(getVOIP().isEnabled())
    {
        if(!list.isEmpty())
        {
            list << m_separator;
        }
        if(getVOIP().contains(m_playersMap.value(cID).ip))
        {
            list << m_VOIPDisconnect;
        }
        else
            list << m_VOIPConnect;
        list << m_VOIPVolume;
    }

    if(!list.isEmpty())
        QMenu::exec(list, m_v_pl->mapToGlobal(pos));
}

void ClientInterface::VOIPRemoveClient()
{
    CLID cID=m_VOIPDisconnect->data().toInt();
    if(cID==0)
        return;
    getVOIP().remove(m_playersMap.value(cID).ip);
    updatePlayerList();
}

void ClientInterface::VOIPAddClient()
{
    CLID cID=m_VOIPConnect->data().toInt();
    if(cID==0)
        return;
    getVOIP().add(m_playersMap.value(cID).ip);
    updatePlayerList();
}

void ClientInterface::VOIPClientVolume()
{
    CLID cID=m_VOIPConnect->data().toInt();
    if(cID==0)
        return;

    bool ok=false;

    double v=QInputDialog::getDouble(this,tr("Volume"),tr("Entrez le volume de réception :"),getVOIP().volume(m_playersMap.value(cID).ip),0,100,2,&ok);

    if(ok)
    {
        getVOIP().setVolume(v, m_playersMap.value(cID).ip);
        updatePlayerList();
    }
}

void ClientInterface::aboutUs()
{
    QString t;
    t = tr("<center><h2>Celendel</h2></center>(Version du %1 - %2)<br/>L'ensemble du projet est sous la licence LGPL.<br/>Personnes ayant participées au développement du programme :<br/>- Gigotdarnaud<br/>- Chidie (Un peu)<br/>- Shade Master (Presque)").arg(__DATE__).arg(__TIME__);
    AboutWindow aw(t, this);
    aw.setWindowTitle(tr("A propos de Celendel"));
    aw.exec();
}

void ClientInterface::playSound(QString lib, QString sound)
{
    lg(tr("Le Maître du Jeu fait jouer : \"%1 - %2\"").arg(lib, sound));
    if(sndMngr.playSound(lib, sound))
        lg(tr("Erreur : son non trouvé."));
}

void ClientInterface::syncSoundLibs(QList<SoundLibInformations> ref)
{
    if(isGM())
        return;

    lg(tr("Informations des bibliothèques sonores requises par le Maître du Jeu reçues :"));
    for(int i=0;i<ref.size();++i)
    {
        if(sndMngr.isLibLoaded(ref[i].name))
        {
            SoundLibInformations sli=sndMngr.getLibInfo(ref[i].name);
            if(sli.version>ref[i].version)
            {
                lg(tr("La bibliothèque <strong>\"%1\"</strong> est chargée, mais votre version est ultérieure à celle du Maître du Jeu.").arg(ref[i].name), false, true);
            }
            else if(sli.version<ref[i].version)
            {
                lg(tr("La bibliothèque <strong>\"%1\"</strong> est chargée, mais votre version est postérieure à celle du Maître du Jeu.").arg(ref[i].name), false, true);
            }
            else
            {
                lg(tr("La bibliothèque <strong>\"%1\"</strong> est chargée et à la bonne version.").arg(ref[i].name), false, true);
            }

            if(sli.sounds!=ref[i].sounds)
                lg(tr("<strong>Erreur</strong> : les listes des sons diffèrent"), false, true);
        }
        else
        {
            lg(tr("<strong>Erreur</strong> : bibliothèque <strong>\"%1\"</strong> non chargée. Certains sons ne pourront <strong>pas</strong> être joués.").arg(ref[i].name), false, true);
        }
    }
}

void ClientInterface::aboutServer()
{
    if(!isConnected())
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Vous n'êtes pas connecté !"));
        return;
    }
    AboutWindow aw(m_motd, this);
    aw.setWindowTitle(tr("Mot du Jour de %1", "Titre de 'about server'").arg(m_serverName));
    aw.exec();
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
    if(cs.exec()==QDialog::Accepted)
    {
        QSettings* set=allocateSettings();

        m_network->setServer(set->value(PARAM_IP).toString(), set->value(PARAM_PORT).toInt());
        m_network->send(ETI(SET_NICK), serialiseSetNickData(set->value(PARAM_NICK).toString()));

        delete set;

        updatePlayerList();
    }
}

void ClientInterface::openSoundsGUI()
{
    SoundsGUI cs(this);
    cs.exec();
}

void ClientInterface::setTitle()
{
    if(!isConnected())
    {
        setWindowTitle(tr("Celendel - Déconnecté"));
        return;
    }
    if(!m_serverName.isEmpty())
    {
        setWindowTitle(tr("Celendel - %1", "Window title").arg(m_serverName));
        return;
    }
    setWindowTitle(tr("Celendel - Connecté", "Window title"));
}

void ClientInterface::connectionEtablished()
{
    QSettings* set=allocateSettings();

    lg(tr("Vous êtes maintenant <strong>connecté</strong> à un serveur (%1:%2) !").arg(m_network->serverIP()).arg(m_network->serverPort()), true, true);
    m_network->send(ETI(SET_NICK), serialiseSetNickData(set->value(PARAM_NICK).toString()));
    m_ac_joinOrLeave->setText(tr("&Se déconnecter du serveur"));
    resetData();

    delete set;
}

void ClientInterface::connectionLost()
{
    lg(tr("Vous avez été déconnecté du serveur. Tappez /retry pour tenter une reconnexion."));
    m_ac_joinOrLeave->setText(tr("&Se connecter au serveur"));
    resetData();
}

void ClientInterface::resetData()
{
    setTitle();
    getVOIP().removeAll();
    m_gameStarted=false;
    m_voted=false;
    m_ID=0;
    m_GMID=0;
    m_location.clear();
    m_motd.clear();
    m_TOD.clear();
    m_serverName.clear();
    m_playersMap.clear();
    m_dictionnariesList->clear();
    m_languageManagement->clear();
    updatePlayerList();
    updateGMLabel();
    updateGMPanel();
}

void ClientInterface::clientJoined(CLID cID, QString IP)
{
    if(cID==m_ID)
        return;

    lg(tr("Un joueur s'est connecté (ID %1).").arg(cID));
    m_playersMap.insert(cID, PlayerInformations("", IP));
    getVOIP().add(IP);
    updatePlayerList();
}

void ClientInterface::clientLeft(CLID cID)
{
    lg(tr("%1 s'est déconnecté.").arg(anonym(cID)));
    getVOIP().remove(m_playersMap[cID].ip);
    m_playersMap.remove(cID);
    updatePlayerList();
}

void ClientInterface::diceRolled(CLID ID, quint16 result, quint16 max)
{
    lg(tr("%1 lance 1d%2, et obtient un %3.").arg(anonym(ID)).arg(max).arg(result));
}

void ClientInterface::rollDice()
{
    m_network->send(ETI(ROLL_DICE), serialiseDiceRollData(0,0,20));
}

void ClientInterface::rollSpecialDice()
{
    bool ok=false;
    int r = QInputDialog::getInt(this, tr("Lancer un dé"), tr("Sélectionnez le nombre de faces"), 20, 2, 2147483647, 1, &ok);
    if(ok)
        m_network->send(ETI(ROLL_DICE), serialiseDiceRollData(0,0,r));
}

void ClientInterface::changeClientNickname(CLID ID, QString nick)
{
    QString old(anonym(ID));
    m_playersMap[ID].name=nick;
    lg(tr("%1 s'appelle maintenant %2.").arg(old).arg(nick));
    updatePlayerList();
}

void ClientInterface::serverName(QString n)
{
    m_serverName=n;
    lg(tr("Le serveur s'appelle maintenant \"%1\".").arg(n));
    setTitle();
}

void ClientInterface::motdChanged(QString n)
{
    m_motd=n;
    lg(tr("Le Message du Jour du serveur a été changé."));
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

    QMap<CLID, PlayerInformations>::const_iterator i = m_playersMap.constBegin();
    while (i != m_playersMap.constEnd())
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
            sti->setText(tr("Maître du Jeu"));
        }
        else
            sti->setText(tr("Simple joueur"));

        item->appendRow(sti);
        }

        if(m_gameStarted)
        {
            QStandardItem *it = new QStandardItem(tr("Rôle :"));
            it->setData(i.key(), DTA_CLID);
            item->appendRow(it);
            QStandardItem* u=new QStandardItem(getRolePlayName(i.key()));
            u->setData(i.key(), DTA_CLID);
            it->appendRow(u);
        }

        {
            QStandardItem *it = new QStandardItem(tr("Addresse IP :"));
            it->setData(i.key(), DTA_CLID);
            item->appendRow(it);
            QStandardItem* u=new QStandardItem(i.value().ip);
            u->setData(i.key(), DTA_CLID);
            it->appendRow(u);
        }
        if(getVOIP().isEnabled())
        {
            QStandardItem *it = new QStandardItem(tr("VOIP :"));
            it->setData(i.key(), DTA_CLID);
            item->appendRow(it);
            bool b=getVOIP().contains(i.value().ip);
            {
                QString txt;
                if(b)
                {
                    txt=tr("Connecté");
                }
                else
                    txt=tr("Non connecté");

                QStandardItem* u=new QStandardItem(txt);
                u->setData(i.key(), DTA_CLID);
                it->appendRow(u);
            }
            if(b)
            {
                QStandardItem* u=new QStandardItem(tr("Volume : %1%").arg(getVOIP().volume(i.value().ip)));
                u->setData(i.key(), DTA_CLID);
                it->appendRow(u);
            }
        }


        ++i;
    }
}

void ClientInterface::updateGMLabel()
{
    if(!m_network->isConnected())
    {
        m_GMLabel->setText(tr("Vous n'êtes pas connecté."));
        m_narrator->setReadOnly(true);
    }
    else if(m_GMID==0)
    {
        m_GMLabel->setText(tr("<strong>Il n'y a actuellement pas de Maître du Jeu.</strong>"));
        m_narrator->setReadOnly(true);
    }
    else if(m_GMID==m_ID)
    {
        m_GMLabel->setText(tr("<strong>Vous êtes actuellement le Maître du Jeu.</strong>"));
        m_narrator->setReadOnly(false);
    }
    else
    {
        m_GMLabel->setText(tr("Le Maître du jeu est <strong>%1</strong>").arg(anonym2(m_GMID)));
        m_narrator->setReadOnly(true);
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
        lg(tr("%1 a voté pour lui-même pour le poste de <strong>Maître de Jeu</strong>.").arg(anonym(f)), true, true);
    }
    else
        lg(tr("%1 a voté pour %2 pour le poste de <strong>Maître de Jeu</strong>.").arg(anonym(f)).arg(anonym(t)), true, true);
    if(m_playersMap.value(t).name=="Lynix")
        lg(tr("Evidement, comme c'est un vote pour Lynix, il ne comptera <strong>pas</strong>. Faut pas rêver !"), false, true);
}

void ClientInterface::changeGameMaster(CLID ID)
{
    m_GMID=ID;

    if(m_GMID==m_ID)
    {
        lg(tr("<strong>Vous</strong> êtes maintenant le <strong>Maître du Jeu</strong>."));
        m_narrator->setReadOnly(false);
        m_network->send(ETI(SYNC_LIBS), serialiseSyncLibsData(sndMngr.getLibsInfo()));
    }
    else
    {
        lg(tr("<em><strong>%1</strong> est maintenant <strong>Maître du Jeu</strong>.</em>").arg(anonym(ID)), true, true);
        m_narrator->setReadOnly(true);
    }
    updatePlayerList();
    updateGMLabel();
    updateGMPanel();
}

void ClientInterface::changeServerInformations(ServerInformations si)
{

    lg(tr("<strong>Mise à jour des informations du serveur :</strong>"));

    if(!si.serverName.isEmpty()&&m_serverName!=si.serverName)
    {
        m_serverName=si.serverName;
        lg(tr("Nom du serveur : %1").arg(m_serverName), false, true);
        setTitle();
    }

    m_motd=si.motd;

    m_scriptManager->updateScriptList(si.scriptList);

    int nms=si.players.size();

    m_playersMap.clear();
    QMap<CLID, PlayerInformations>::const_iterator i = si.players.constBegin(); //Manual copy - operator=() seems to be broken for empty values like QString("")... I realy don't know why (Gigotdarnaud, 2 July 2010)
    while (i != si.players.constEnd())
    {
        m_playersMap.insert(i.key(),i.value());
        if(!getVOIP().contains(i.value().ip))
        {
            getVOIP().add(i.value().ip);
        }
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
        if(m_GMID==m_ID)
        {
            m_narrator->setReadOnly(false);
        }
        else
            m_narrator->setReadOnly(true);

        updateGMLabel();
    }

    m_narrator->setHtml(si.narration);
    m_narrator->moveCursor(QTextCursor::End);

    syncLanguagesList(si.languages);
    syncDictionariesList(si.dictionaries);

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
    QString nick=m_playersMap.value(ID).name;

    if(nick.isEmpty())
        return tr("Client anonyme %1").arg(ID);

    return nick;
}

QString ClientInterface::anonym(CLID ID)
{
    QString nick=m_playersMap.value(ID).name;

    if(nick.isEmpty())
        return tr("Le client anonyme [%1]").arg(ID);

    if(m_GMID == ID)
        return tr("(MJ) %1[%2]").arg(nick).arg(ID);

    return tr("%1[%2]").arg(nick).arg(ID);
}

void ClientInterface::syncLanguagesList(QList<QPair<QString, QString> > languages)
{
    QStringList l;
    for(int i=0,m=languages.size();i<m;++i)
    {
        l.append(languages[i].first);
    }

    QString current=m_RPLanguage->currentText();
    m_RPLanguage->clear();

    m_RPLanguage->addItems(l);
    int a=m_RPLanguage->findText(current);
    m_RPLanguage->setCurrentIndex(a==-1?0:a);
}

QString ClientInterface::getRolePlayName(CLID ID)
{
    QString n=m_characterMngr->getPlayerCharacter(m_playersMap.value(ID).name);
    if(n.isEmpty())
        return m_playersMap.value(ID).name;

    return n;
}

void ClientInterface::chat(CLID sender, QString lang, QString txt, ENUM_TYPE canal)
{
    if(canal==NORMAL)
    {
        lg(anonym(sender)+" : "+txt);
    }
    else if(canal==RP)
    {
        if(!lang.isEmpty())
            lang="["+lang+"] ";
        m_RPChat->append(getRolePlayName(sender) + " : " + lang + txt);
    }
    else if(canal==SELF_NARRATOR)
    {
        m_RPChat->append(getRolePlayName(sender) + " " + txt);
        m_narrator->append(getRolePlayName(sender) + " " + txt);
    }
}
