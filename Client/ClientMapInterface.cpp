#include "ClientInterface.h"
#include "MapEditor.h"
#include <QDebug>
#include "..\Shared\Serializer.h"

bool ClientInterface::loadRessourcesListGUI()
{
  /*  QString file=QFileDialog::getOpenFileName(this,tr("Charger une liste d'images"),QString(),tr("Fichiers de liste (*.list);;Tous les fichiers (*.*)"));
    if(file.isEmpty())
        return true;

    prev:
    QMessageBox::StandardButton but=QMessageBox::question(this,tr("Exclusivité ?"),tr("Voulez-vous décharger d'abord les ressources actuelles (exclusivité) ?"),QMessageBox::Yes|QMessageBox::No|QMessageBox::Abort|QMessageBox::Help);

    if(but==QMessageBox::Abort)
        return true;
    if(but==QMessageBox::Help)
    {
        QMessageBox::information(this, tr("Lire tu dois, jeune padawan"), tr("\"L'exclusivité\" d'un set d'image est lorsque ce set d'image est chargé, dans l'ordre, dans le cache de ressource interne du moteur de rendu. Ainsi, chaque image d'une liste en mode \'exclusif\' aura systématiquement le même RSID, ce qui est essentiel pour une carte. Cependant, ce mode d'ouverture implique de vider le cache entièrement, et si une carte est déjà chargée son set d'image sera remplacé. Notez que pour des raisons de modularité (traduisez, parce que le programmeur était trop feignant pour faire un ressource manager), chaque fenêtre de rendu possède son propre cache d'image, et que seul le cache de la carte principale sera vidangé dans votre cas."));
        goto prev; // Why are you starring at me ? Is it THAT bad ? I don't care, I love spaghetti anyway.
    }

    m_mapWi->loadRessourcesPack(file, but==QMessageBox::Yes);*/

    return 0;//m_mapWi->loadRessourcesPack(file, but==QMessageBox::Yes).isEmpty();
}

void ClientInterface::openMapEditor()
{
    delete m_mapEditor;
    m_mapEditor = new MapEditor(this);
    m_mapEditor->setSendingButtonEnabled(isGM());
    connect(m_mapEditor, SIGNAL(mapSendingRequested(const MapInformations* const)), this, SLOT(sendMapToServer(const MapInformations* const)));
    m_mapEditor->show();
}

bool ClientInterface::openRenderWindow(QString mapName, QString ressList)
{
    m_renderedMap=NULL;

    if(mapName.isEmpty())
    {
        mapName=QFileDialog::getOpenFileName(this, tr("Charger une carte"),QString(),tr("Fichiers de carte (*.map);;Tous les fichiers (*.*)"));
        if(mapName.isEmpty())
            return true;

    }
    if(ressList.isEmpty())
    {
       ressList=QFileDialog::getOpenFileName(this,tr("Charger une liste d'images"),QString(),tr("Fichiers de liste (*.list);;Tous les fichiers (*.*)"));
        if(ressList.isEmpty())
            return true;
    }

    QDialog dia(this);

    MapWidget* mapRender = new MapWidget(&dia);
    mapRender->setHighlight(true);
    if(mapRender->loadRessourcesPack(ressList).isEmpty()||mapRender->setMap(mapName))
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Impossible de charger la carte \"%1\" ou le set d'image \"%2\".").arg(mapName).arg(ressList));
        return true;
    }

    QPushButton sendToServer(tr("Envoyer la carte au serveur"));

    if(!isGM())
        sendToServer.hide();

    m_renderedMap=mapRender->getMap();

    connect(&sendToServer, SIGNAL(pressed()), this, SLOT(sendMapToServer()));

    QHBoxLayout l;
    l.addWidget(mapRender);
    l.addWidget(&sendToServer);
    dia.setLayout(&l);
    dia.exec();
    m_renderedMap=NULL;
    return false;
}

void ClientInterface::sendMapToServer(const MapInformations* const map)
{
    if(!isGM())
        return;
    if(map==NULL||!map->isValid())
        return;

    m_network->send(ETI(MAP_INFORMATIONS), serialiseMapInformationsData(*map));
}

void ClientInterface::sendMapToServer()
{
    if(!isGM())
        return;
    if(m_renderedMap==NULL)
        return;

    m_network->send(ETI(MAP_INFORMATIONS), serialiseMapInformationsData(*m_renderedMap));
}

