#include "ClientInterface.h"
#include "MapEditor.h"
#include <QDebug>
#include "..\Shared\Serializer.h"

void ClientInterface::openMapEditor()
{
    delete m_mapEditor;
    m_mapEditor = new MapEditor(this);
    connect(m_mapEditor, SIGNAL(closed()), this, SLOT(clearMapEditor()));
    m_mapEditor->setSendingButtonEnabled(isGM());
    connect(m_mapEditor, SIGNAL(mapSendingRequested(const MapInformations* const,const QMap<QString, RSID>&)), this, SLOT(sendMapToServer(const MapInformations* const,const QMap<QString, RSID>&)));
    m_mapEditor->show();
}

void ClientInterface::clearMapEditor()
{
    delete m_mapEditor;
    m_mapEditor=NULL;
}

void ClientInterface::sendMapToServer(const MapInformations* const map, const QMap<QString, RSID>& ress)
{
    if(!isGM())
        return;
    if(map==NULL||!map->isValid())
        return;

    m_network->send(ETI(MAP_INFORMATIONS), serialiseMapInformationsData(*map));
    if(!ress.isEmpty())
        m_network->send(ETI(UPDATE_RESSOURCES), serialiseUpdateRessourcesData(ress));
}

void ClientInterface::mapFlare()
{

}
