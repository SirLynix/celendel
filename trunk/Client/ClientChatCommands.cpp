#include "ClientInterface.h"
#include "..\Shared\Serializer.h"

CLID ClientInterface::CLIDFromString(const QString& str) //Zero on error
{
    bool ok=false;
    CLID ID = str.toInt(&ok);
    if(ok)
        return ID;

    return m_nickMap.key(str, 0);
}

void ClientInterface::sendMessage()
{
    QString txt = m_chatInput->text().simplified();
    if(txt.isEmpty())
        return;

    m_chatInput->setText("");

    if(txt.startsWith(tr("/retry")))
    {
        if(!m_network->isConnected())
            m_network->connection();
        return;
    }
    else if(txt.startsWith(tr("/aide")))
    {
        lg(tr("Liste des commandes :"));
        lg(tr("Note : remplacez <strong>[Client ID]</strong> par l'ID du client OU son pseudo ENTIER (si non anonyme)."), false, true);


        lg(tr("<br />Commandes de canal :"), false, true);
        lg("<strong>" + tr("/rp") + "</strong> | <strong>" + tr("/jdr") + "</strong>" + tr("<em>[Texte]</em> : Ecrire du dialogue, au format [Personnage : Blah]."), false, true);
        lg("<strong>" + tr("/me") + "</strong> | <strong>" + tr("/moi") + "</strong>" + tr("<em>[Texte]</em> : Ecrire de la narration, au format [Personnage fait quelque chose]."), false, true);
        lg("<strong>" + tr("/nar") + "</strong>" + tr("<em>[Texte]</em> : <strong>(MJ)</strong> Ecrire en tant que narrateur."), false, true);
        lg("<strong>" + tr("/1d20") + "</strong>" + tr(" : Lancer 1d20."), false, true);

        lg(tr("<br />Commandes locales :"), false, true);
        lg("<strong>" + tr("/retry") + "</strong>" + tr(" : Tenter de se re-connecter au serveur (sans effet si déjà connecté)."), false, true);
        lg("<strong>" + tr("/partir") + "</strong> | <strong>" + tr("/quitter") + "</strong> | <strong>" + tr("/sortir") + "</strong>" + tr(" : Fermer le client."), false, true);
        lg("<strong>" + tr("/ping") + "</strong>" + tr(" : Affiche le dernier ping."), false, true);
        lg("<strong>" + tr("/aide") + "</strong>" + tr(" : Afficher ces informations."), false, true);

        lg(tr("<br />Commandes d'administration :"), false, true);
        lg("<strong>" + tr("/pseudo") + "</strong>" + tr(" <em>[Pseudo]</em> : Changer de pseudo sur le chat. Caractères autorisés : \"[a-Z][0-9]-_éèà'\""), false, true);
        lg("<strong>" + tr("/votemj") + "</strong>" + tr(" <em>[Client ID]</em> : Voter pour qu'un joueur devienne MJ - un seul vote par partie."), false, true);

        lg(tr("<br />Commandes d'administration (Maître du Jeu uniquement) :"), false, true);
        lg("<strong>" + tr("/kick") + "</strong>" + tr(" <em>[Client ID] [Raison]</em> : <strong>(MJ)</strong> Ejecte un client du serveur."), false, true);
        lg("<strong>" + tr("/ban") + "</strong>" + tr(" <em>[Client ID] [Raison]</em> : <strong>(MJ)</strong> Banni un client du serveur (par IP, valable jusqu'au redémarage du serveur)."), false, true);
        lg("<strong>" + tr("/unban") + "</strong>" + tr(" <em>[IP]</em> : <strong>(MJ)</strong> Supprime une IP de la banlist."), false, true);
        lg("<strong>" + tr("/son") + "</strong>" + tr(" <em>[Ressource ID]</em> : <strong>(MJ)</strong> Joue un son chez tous les clients."), false, true);
        lg("<strong>" + tr("/lancerpartie") + "</strong>" + tr(" : <strong>(MJ)</strong> Lancer la partie."), false, true);
        lg("<strong>" + tr("/changemj") + "</strong>" + tr(" <em>[Client ID]</em> : <strong>(MJ)</strong> Changer le MJ. Attention, vous perdrez vos privilèges."), false, true);
        lg("<strong>" + tr("/nomserveur") + "</strong>" + tr(" <em>[Nom]</em> : <strong>(MJ)</strong> Changer le nom du serveur."), false, true);
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
            m_network->send(ETI(GTFO_LYNIX), serialiseGTFOLynixData(CLIDFromString(spl[1]), ETI(KICK), r));
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
            m_network->send(ETI(GTFO_LYNIX), serialiseGTFOLynixData(CLIDFromString(spl[1]), ETI(BAN), r));
        }
        else if(txt.startsWith(tr("/unban")))
        {
            QStringList spl = txt.split(' ', QString::SkipEmptyParts);
            if(spl.size()<2)
            {
                lg(tr("Erreur : pas assez d'arguments."));
                return;
            }

            m_network->send(ETI(UNBAN), serialiseUnbanData(spl[1]));
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

            m_network->send(ETI(GM_ELECT), serialiseGMElectData(CLIDFromString(spl[1])));
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

            m_network->send(ETI(NEW_GM), serialiseNewGMData(CLIDFromString(spl[1])));
        }
        else if(txt.startsWith(tr("/lancerpartie"), Qt::CaseInsensitive))
        {
            m_network->send(ETI(LAUNCH_GAME), QByteArray());
            show=false;
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
        else if(txt.startsWith(tr("/1d20")))
        {
            rollDice();
            show=false;
        }
        else if(txt.startsWith(tr("/nomserveur")))
        {
            QStringList spl = txt.split(' ', QString::SkipEmptyParts);
            QString r;
            if(spl.size()<2)
            {
                lg(tr("Erreur : pas assez d'arguments."));
                return;
            }

            m_network->send(ETI(SERVER_NAME), serialiseServerNameData(txt.mid( spl[0].size()).trimmed()));
        }
    }

    if(show)
        m_network->send(ETI(CHAT), serialiseChatData(ETI(NORMAL), txt, 0));

}

