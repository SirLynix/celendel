#include "ClientInterface.h"
#include "..\Shared\Serializer.h"

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
        return;
    }
    else if(txt.startsWith(tr("/partir"))||txt.startsWith(tr("/quitter"))||txt.startsWith(tr("/sortir")))
    {
        qApp->quit();
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
            if(txt.trimmed()==tr("/pseudo"))
                lg(tr("Erreur : pas assez d'arguments."));

            m_network->send(ETI(SET_NICK), serialiseSetNickData(txt.mid( tr("/pseudo").size() )));
            show=false;
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
    }

    if(show)
        m_network->send(ETI(CHAT), serialiseChatData(ETI(NORMAL), txt, 0));

}

