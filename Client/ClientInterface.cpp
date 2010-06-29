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
    if(!m_network->isConnected())
    {
        return;
    }

    QString txt = m_chatInput->text().simplified();
    if(txt.isEmpty())
        return;

    if(txt[0]=='/')
    {
        if(txt.startsWith(tr("/pseudo")))
        {
            m_network->send(ETI(SET_NICK), serialiseSetNickData(txt.mid( tr("/pseudo").size() )));
        }
        else if(txt.startsWith(tr("/ping")))
        {
            if(m_network->isConnected())
            {
                lg(tr("Ping actuel : %1ms").arg(m_network->getPing()));
                m_network->ping();
            }
            else
                lg(tr("Vous n'êtes pas connecté !"));
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
            QStringList spl = txt.split(' ');
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
            QStringList spl = txt.split(' ');
            QString r;
            if(spl.size()<2)
            {
                lg(tr("Erreur : pas assez d'arguments."));
                return;
            }

            m_network->send(ETI(GM_ELECT), serialiseGMElectData(spl[1].toInt()));
        }
        else if(txt.startsWith(tr("/changemj"), Qt::CaseInsensitive))
        {
            QStringList spl = txt.split(' ');
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
            qApp->quit();
        }
        else if(txt.startsWith(tr("/aide")))
        {
            log(tr("Liste des commandes :"));
            log(tr("/pseudo") + tr(" [pseudo] : Changer de pseudo sur le chat."), false);
            log(tr("/ping") + tr(" : Affiche le dernier ping."), false);
            log(tr("/kick") + tr(" [Client ID] [Raison] : (MJ) Ejecte un client du serveur."), false);
            log(tr("/ban") + tr(" [Client ID] [Raison] : (MJ) Banni un client du serveur (par IP, valable jusqu'au redémarage du serveur)."), false);
            log(tr("/son") + tr(" [Ressource ID] : (MJ) Joue un son chez tous les clients."), false);
            log(tr("/votemj") + tr(" [Client ID] : Voter pour qu'un joueur devienne MJ - un seul vote par partie."), false);
            log(tr("/changemj") + tr(" [Client ID] : (MJ) Changer le MJ. Attention, vous perdrez vos privilèges."), false);
        }
    }

    m_network->send(ETI(CHAT), serialiseChatData(ETI(NORMAL), txt, 0));

    m_chatInput->setText("");
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

void ClientInterface::changeServerInformations(ServerInformations si)
{
    m_GMID=si.gameMasterID;
    m_location=si.location;
    m_TOD=si.timeOfDay;
    m_serverName=si.serverName;
    m_nickMap=si.playersName;
    m_gameStarted=si.gameStarted;
}

void ClientInterface::chat(CLID sender, QString text, ENUM_TYPE canal)
{
    if(canal==NORMAL)
    {
        lg(m_nickMap.value(sender)+"["+QString::number(sender)+"] : "+text);
    }
}
