#include "ClientInterface.h"
#include "MapWidget.h"
#include <QDebug>

bool ClientInterface::loadRessourcesListGUI()
{
    QString file=QFileDialog::getOpenFileName(this,tr("Charger une liste d'images"),QString(),tr("Fichiers de liste (*.list);;Tous les fichiers (*.*)"));
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

    qDebug() << m_mapWi->loadRessourcesPack(file, but==QMessageBox::Yes);

    return 0;//m_mapWi->loadRessourcesPack(file, but==QMessageBox::Yes).isEmpty();
}

bool ClientInterface::openRenderWindow(QString mapName, QString ressList)
{
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
    MapWidgetScroll* mapRenderWidg = new MapWidgetScroll(&dia);
    MapWidget* mapRender = mapRenderWidg->getMapWidget();
    if(mapRender->loadRessourcesPack(ressList).isEmpty()||mapRender->setMap(mapName))
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Impossible de charger la carte \"%1\" ou le set d'image \"%2\".").arg(mapName).arg(ressList));
        return true;
    }

    QHBoxLayout l;
    l.addWidget(mapRenderWidg);
    dia.setLayout(&l);
    dia.exec();
    return false;
}

