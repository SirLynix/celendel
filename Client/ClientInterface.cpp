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
}

void ClientInterface::lg(const QString txt, bool time, bool html)
{
    QString tmp;
    if(time)
    {
        tmp += QTime::currentTime().toString("HH:mm:ss") + " : ";
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

void ClientInterface::connectionEtablished()
{
    lg(tr("Vous êtes maintenant connecté à un serveur (%1:%2) !").arg(m_network->serverIP()).arg(m_network->serverPort()));
}

void ClientInterface::connectionLost()
{
    lg(tr("Vous avez été déconnecté du serveur. Tappez /retry pour tenter une reconnexion."));
}

void ClientInterface::diceRolled(CLID ID, quint16 result)
{
    lg(tr("%1 lance 1d20, et obtient un %2.").arg(anonym(ID)).arg(result));
}

void ClientInterface::changeClientNickname(CLID ID, QString nick)
{
    QString old(anonym(ID));
    m_nickMap[ID]=nick;
    lg(tr("%1 s'appelle maintenant %2.").arg(old).arg(nick));

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
    lg(tr("%1 a voté pour %2 pour le poste de <strong>Maître de Jeu</strong>.").arg(anonym(f)).arg(anonym(t)), true, true);
    if(m_nickMap.value(t)=="Lynix")
        lg(tr("Evidement, comme c'est un vote pour Lynix, il ne comptera <strong>pas</strong>. Faut pas rêver !"), false, true);
}

void ClientInterface::changeGameMaster(CLID ID)
{
    m_GMID=ID;
    lg(tr("<em><strong>%1</strong> est maintenant <strong>Maître du Jeu</strong>.</em>").arg(m_nickMap.value(ID)), true, true);
    if(m_nickMap.value(ID)=="Gigotdarnaud")
        lg(tr("Tremblez, mortels ! Le grand <strong>Gigotdarnaud</strong> arrive !"), false, true);
}

void ClientInterface::changeServerInformations(ServerInformations si)
{

    lg(tr("<strong>Mise à jour des informations du serveur :</strong>"));

    if(!si.serverName.isEmpty()&&m_serverName!=si.serverName)
    {
        lg(tr("Nom du serveur : %1").arg(m_serverName), false, true);
        m_serverName=si.serverName;
    }

    int nms=si.playersName.size();
    if(si.playersName != m_nickMap)
    {
        m_nickMap==si.playersName;
        if(nms==1)
        {
            lg(tr("<em>Vous êtes le seul client connecté.</em>"), false, true);
        }
        else
        {
            lg(tr("<strong>%n</strong> client(s) connecté(s) :","",nms), false, true);
            QMap<CLID, QString>::const_iterator i = m_nickMap.constBegin();
            while (i != m_nickMap.constEnd())
            {
                if(i.key()==m_ID)
                {
                    lg(tr("%1 (vous)").arg(anonym(i.key())), false);
                }
                else
                    lg(anonym(i.key()), false);
                ++i;
            }
        }
    }

    if(m_GMID!=si.gameMasterID && si.gameMasterID!=0)
    {
        lg(tr("<em><strong>%1</strong> est <strong>Maître du Jeu</strong></em>").arg(anonym(m_GMID)), false, true);
        m_GMID=si.gameMasterID;
    }

    if(si.gameStarted)
    {
        if(m_gameStarted!=si.gameStarted)
        {
            lg(tr("<em>La partie a déjà démarré.</em>"), false, true);
            m_gameStarted=si.gameStarted;
        }
        if(si.location!=m_location && !m_location.isEmpty())
        {
            lg(tr("<em>Lieu du RP</em> : %1").arg(m_location), false, true);
            m_location=si.location;
        }
        if(si.timeOfDay!=m_TOD && !m_TOD.isEmpty())
        {
            lg(tr("<em>Heure du RP :</em> %1").arg(m_TOD), false, true);
            m_TOD=si.timeOfDay;
        }
    }
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
