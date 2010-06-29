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
}

void ClientInterface::lg(const QString txt, bool time)
{
    QString tmp;
    if(time)
    {
        tmp += QTime::currentTime().toString("HH:mm:ss") + " : ";
    }
    tmp+=txt;
    m_chat->append(tmp.toAscii());
}

void ClientInterface::sendMessage()
{
    QString txt = m_chatInput->text().simplified();
    if(txt.isEmpty())
        return;

    if(txt.startsWith(tr("/retry")))
    {
        if(!m_network->isConnected())
            m_network->connection();
        return;
    }

    if(!m_network->isConnected())
    {
        lg(tr("Vous n'êtes pas connecté !"));
        return;
    }


    bool show=true;

    m_chatInput->setText("");

    if(txt[0]=='/')
    {
        if(txt.startsWith(tr("/pseudo")))
        {
            m_network->send(ETI(SET_NICK), serialiseSetNickData(txt.mid( tr("/pseudo").size() )));
        }
        else if(txt.startsWith(tr("/ping")))
        {
            lg(tr("Ping actuel : %1ms").arg(m_network->getPing()));
            m_network->ping();
            show=false;
        }
        else if(txt.startsWith(tr("/kick")))
        {
            QStringList spl = txt.split(' ');
            QString r;
            if(spl.size()<2)
            {
                lg(tr("Erreur : pas assez d'arguments."));
                return;
            }
            else if(spl.size()>3)
            {
                r=txt.mid(txt.indexOf(spl[2]));
            }
            m_network->send(ETI(GTFO_LYNIX), serialiseGTFOLynixData(spl[1].toInt(), ETI(KICK), r));
        }
        else if(txt.startsWith(tr("/ban")))
        {
            QStringList spl = txt.split(' ', QString::SkipEmptyParts);
            QString r;
            if(spl.size()<2)
            {
                lg(tr("Erreur : pas assez d'arguments."));
                return;
            }
            else if(spl.size()>3)
            {
                r=txt.mid(txt.indexOf(spl[2]));
            }
            m_network->send(ETI(GTFO_LYNIX), serialiseGTFOLynixData(spl[1].toInt(), ETI(BAN), r));
        }
        else if(txt.startsWith(tr("/son")))
        {
            QStringList spl = txt.split(' ', QString::SkipEmptyParts);
            QString r;
            if(spl.size()<2)
            {
                lg(tr("Erreur : pas assez d'arguments."));
                return;
            }

            m_network->send(ETI(PLAY_SOUND), serialisePlaySoundData(spl[1].toInt()));
        }
        else if(txt.startsWith(tr("/votemj"), Qt::CaseInsensitive))
        {
            QStringList spl = txt.split(' ', QString::SkipEmptyParts);
            QString r;
            if(spl.size()<2)
            {
                lg(tr("Erreur : pas assez d'arguments."));
                return;
            }

            m_network->send(ETI(GM_ELECT), serialiseGMElectData(spl[1].toInt()));
            show=false;
        }
        else if(txt.startsWith(tr("/changemj"), Qt::CaseInsensitive))
        {
            QStringList spl = txt.split(' ', QString::SkipEmptyParts);
            QString r;
            if(spl.size()<2)
            {
                lg(tr("Erreur : pas assez d'arguments."));
                return;
            }

            m_network->send(ETI(NEW_GM), serialiseNewGMData(spl[1].toInt()));
        }
        else if(txt.startsWith(tr("/lancerpartie"), Qt::CaseInsensitive))
        {
            m_network->send(ETI(LAUNCH_GAME), QByteArray());
        }
        else if(txt.startsWith(tr("/partir"))||txt.startsWith(tr("/quitter"))||txt.startsWith(tr("/sortir")))
        {
            show=false;
            qApp->quit();
        }
        else if(txt.startsWith(tr("/me"))||txt.startsWith(tr("/moi")))
        {
            QStringList spl = txt.split(' ', QString::SkipEmptyParts);
            QString r;
            if(spl.size()<2)
            {
                lg(tr("Erreur : pas assez d'arguments."));
                return;
            }

            m_network->send(ETI(CHAT), serialiseChatData(ETI(SELF_NARRATOR), txt.mid( spl[0].size()).simplified(), 0));
            show=false;
        }
        else if(txt.startsWith(tr("/rp"))||txt.startsWith(tr("/jdr")))
        {
            QStringList spl = txt.split(' ', QString::SkipEmptyParts);
            QString r;
            if(spl.size()<2)
            {
                lg(tr("Erreur : pas assez d'arguments."));
                return;
            }

            m_network->send(ETI(CHAT), serialiseChatData(ETI(RP), txt.mid( spl[0].size()).simplified(), 0));
            show=false;
        }
        else if(txt.startsWith(tr("/nar")))
        {
            QStringList spl = txt.split(' ', QString::SkipEmptyParts);
            QString r;
            if(spl.size()<2)
            {
                lg(tr("Erreur : pas assez d'arguments."));
                return;
            }

            m_network->send(ETI(CHAT), serialiseChatData(ETI(NARRATOR), txt.mid( spl[0].size()).trimmed(), 0));
            show=false;
        }
        else if(txt.startsWith(tr("/aide")))
        {
            lg(tr("Liste des commandes :"));
            lg(tr("/aide") + tr(" : Afficher ces informations."));
            lg(tr("/pseudo") + tr(" [pseudo] : Changer de pseudo sur le chat."), false);
            lg(tr("/ping") + tr(" : Affiche le dernier ping."), false);
            lg(tr("/kick") + tr(" [Client ID] [Raison] : (MJ) Ejecte un client du serveur."), false);
            lg(tr("/ban") + tr(" [Client ID] [Raison] : (MJ) Banni un client du serveur (par IP, valable jusqu'au redémarage du serveur)."), false);
            lg(tr("/son") + tr(" [Ressource ID] : (MJ) Joue un son chez tous les clients."), false);
            lg(tr("/votemj") + tr(" [Client ID] : Voter pour qu'un joueur devienne MJ - un seul vote par partie."), false);
            lg(tr("/changemj") + tr(" [Client ID] : (MJ) Changer le MJ. Attention, vous perdrez vos privilèges."), false);
            lg(tr("/lancerpartie") + tr(" : (MJ) Lancer la partie."), false);
            lg(tr("/partir") + " | " + tr("/quitter") + " | " + tr("/sortir") + tr(" : Fermer le client."), false);
            lg(tr("/rp") + " | " + tr("/jdr") + tr(" : Ecrire du dialogue, au format [Personnage : Blah]."), false);
            lg(tr("/me") + " | " + tr("/moi") + tr(" : Ecrire de la narration, au format [Personnage fait quelque chose]."), false);
            lg(tr("/nar") + tr(" : (MJ) Ecrire en tant que narrateur."), false);
            show=false;
        }
    }

    if(show)
        m_network->send(ETI(CHAT), serialiseChatData(ETI(NORMAL), txt, 0));

}

void ClientInterface::changeClientNickname(CLID ID, QString nick)
{
    if(m_nickMap.value(ID)!="")
    {
        lg(tr("%1 s'appelle maintenant %2 (ID %3).").arg(m_nickMap.value(ID)).arg(nick).arg(ID));
    }
    else
    {
        lg(tr("Le client anonyme ID %1 s'appelle maintenant %2.").arg(ID).arg(nick));
    }
    m_nickMap[ID]=nick;

}

void ClientInterface::showError(ENUM_TYPE e, QString txt)
{
    lg(tr("Erreur : %1").arg(ETS(e, txt)));
}

void ClientInterface::changeClientID(CLID ID)
{
    m_ID=ID;
}

void ClientInterface::clientVoted(CLID f, CLID t)
{
    lg(m_nickMap.value(f)+"["+QString::number(f)+"] a voté pour  "+m_nickMap.value(t)+"["+QString::number(t)+"] pour le poste de Maître de Jeu.");
    if(m_nickMap.value(t)=="Lynix")
        lg(tr("Evidement, comme c'est un vote pour Lynix, il ne comptera pas. Faut pas rêver !"));
}

void ClientInterface::changeGameMaster(CLID ID)
{
    m_GMID=ID;
    lg(tr("%1 est maintenant Maître du Jeu.").arg(m_nickMap.value(ID)));
    if(m_nickMap.value(ID)=="Gigotdarnaud")
        lg(tr("Tremblez, mortels ! Le grand Gigotdarnaud arrive !"));
}

void ClientInterface::changeServerInformations(ServerInformations si)
{
    m_GMID=si.gameMasterID;
    m_location=si.location;
    m_TOD=si.timeOfDay;
    m_serverName=si.serverName;
    m_nickMap=si.playersName;
    m_gameStarted=si.gameStarted;
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
        lg(m_nickMap.value(sender)+"["+QString::number(sender)+"] : "+txt);
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
