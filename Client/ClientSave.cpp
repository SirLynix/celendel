#include "ClientInterface.h"

#define VERSION static_cast<qint32>(0)
#define MAGIC_NUMBER (quint32)0x1337C0D3
#include <QDateTime>
#include "EntitiesManager.h"
#include "SoundManager.h"
#include "../Shared/Serializer.h"

void ClientInterface::saveGame()
{
    QString fileName=QFileDialog::getSaveFileName(this, tr("Sauvegarder une partie"), QString(), tr("Fichiers de sauvegarde (*%1)").arg(SAVE_EXT));
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "ERROR : cannot open file " << fileName << " for writing, abording...";
        QMessageBox::critical (this, tr("Echec de la sauvegarde"), tr("Impossible d'ouvrir le fichier \"%1\" en écriture.").arg(fileName));
        return;
    }

    QByteArray dta;
    QDataStream out(&dta, QIODevice::ReadWrite);

    out << MAGIC_NUMBER;
    out << VERSION;
    out << QDateTime::currentDateTime();
    out << m_network->serverIP();
    out << m_network->serverPort();
    out << m_gameStarted;
    out << m_voted;
    out << m_ID;
    out << m_GMID;
    out << m_location;
    out << m_TOD;
    out << m_serverName;
    out << m_motd;
    out << m_playersMap;
    out << m_chat->toHtml();
    out << m_narrator->toHtml();
    out << m_RPChat->toHtml();
    out << sndMngr.loadedLibs();
    out << *m_entitiesManager;

    file.write(qCompress(dta));

    QMessageBox::information(this, tr("Sauvegarde terminée !"), tr("Partie sauvée dans le fichier \"%1\".").arg(fileName));
}

void ClientInterface::loadGame()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Charger une partie"), QString(), tr("Fichiers de sauvegarde (*%1)").arg(SAVE_EXT));
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "ERROR : cannot open file " << fileName << " for reading, abording...";
        QMessageBox::critical (this, tr("Echec de l'ouverture de la sauvegarde"), tr("Impossible d'ouvrir le fichier \"%1\" en lecture.").arg(fileName));
        return;
    }
    QByteArray dta=qUncompress(file.readAll());
    if(dta.isEmpty())
    {
        QMessageBox::critical (this, tr("Echec de l'ouverture de la sauvegarde"), tr("Impossible d'ouvrir le fichier \"%1\" : son format est invalide.").arg(fileName));
        return;
    }

    m_network->disconnection();

    QDataStream in(&dta, QIODevice::ReadOnly);

    quint32 magicNumber;
    in >> magicNumber;
    if(magicNumber!=MAGIC_NUMBER)
    {
        QMessageBox::critical (this, tr("Echec de l'ouverture de la sauvegarde"), tr("Impossible d'ouvrir le fichier \"%1\" : son format est invalide.").arg(fileName));
        return;
    }
    qint32 version;
    in >> version;
    if(version != VERSION)
    {
        QMessageBox::critical (this, tr("Echec de l'ouverture de la sauvegarde"), tr("Impossible d'ouvrir le fichier \"%1\" : son format est trop ancien ou trop récent.").arg(fileName));
        return;
    }

    QDateTime date;
    in >> date;
    QString ip; quint16 port;
    in >> ip; in >> port; m_network->setServer(ip, port);
    in >> m_gameStarted;
    in >> m_voted;
    in >> m_ID;
    in >> m_GMID;
    in >> m_location;
    in >> m_TOD;
    in >> m_serverName;
    in >> m_motd;
    in >> m_playersMap;
    QString t;
    in >> t; m_chat->setHtml(t);
    in >> t; m_narrator->setHtml(t);
    in >> t; m_RPChat->setHtml(t);
    QStringList libs;
    in >> libs;
    sndMngr.setLibList(libs);
    in >> *m_entitiesManager;

    QMessageBox::information(this, tr("Partie chargée avec succès !"), tr("Partie chargée avec succès depuis le fichier \"%1\".").arg(fileName));
}
