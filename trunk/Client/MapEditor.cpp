#include "MapEditor.h"
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>

MapEditor::MapEditor(QWidget* parent, const QString& map):QMainWindow(parent)
{
    m_mapWidgetScroll = new MapWidgetScroll(this);

    setCentralWidget(m_mapWidgetScroll);

    QMenu *fileMenu = menuBar()->addMenu(tr("&Fichier"));
    QAction *ac_save = fileMenu->addAction(tr("&Sauvegarder la carte..."));
    QAction *ac_saveAs = fileMenu->addAction(tr("&Sauvegarder sous..."));
    QAction *ac_quit = fileMenu->addAction(tr("&Quitter..."));

    m_mapName=map;
    if(!map.isEmpty())
    {
        loadMap(map);
    }
}

bool MapEditor::loadMap(QString mapName)
{
    if(mapName.isEmpty())
        mapName = QFileDialog::getOpenFileName(this, tr("Charger une carte..."));

    if(mapName.isEmpty())
        return true;


    return m_mapWidgetScroll->getMapWidget()->setMap(mapName);
}
