#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QDockWidget>
#include <QLayout>

#include <QSpinBox>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QInputDialog>
#include <QCloseEvent>
#include <QListWidget>
#include <QModelIndex>
#include <QGroupBox>
#include <QRegExp>
#include <QLineEdit>
#include <QProgressDialog>
#include <limits>

#include "QColorPicker/QColorViewer.h"
#include "MapEditorDialogs.h"

#include "MapEditor.h"

#define UPDATE_DELAY

MapEditor::MapEditor(QWidget* par, const QString& map, const QString& ressourceList):QMainWindow(par)
{
    m_mapWidget = NULL; m_currentItemIndex=0;

    pgrdia=new QProgressDialog(tr("Chargement en cours..."), tr("Veuillez patienter.."), 0, 100, this);
    pgrdia->setWindowModality(Qt::WindowModal);
    pgrdia->setMinimumDuration(100);
    pgrdia->hide();

    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);
    setDockNestingEnabled(true);

    m_rsRegExp.setPatternSyntax(QRegExp::Wildcard);

    setWindowTitle(tr("Éditeur de carte"));

    { ///MAP PROPERTIES DOCK
    QDockWidget* dw_mapProperties = new QDockWidget(tr("Propriétés de la carte"), this);
    dw_mapProperties->setWhatsThis(tr("Un dock regroupant quelques propriétés de la carte"));
    dw_mapProperties->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dw_mapProperties->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
    QWidget *w_mapProperties = new QWidget(dw_mapProperties);
    dw_mapProperties->setWidget(w_mapProperties);

    addDockWidget(Qt::TopDockWidgetArea, dw_mapProperties);

    QVBoxLayout *l_mapProperties = new QVBoxLayout(w_mapProperties);
    w_mapProperties->setLayout(l_mapProperties);

    {
        QHBoxLayout *lay=new QHBoxLayout();
        l_mapProperties->addLayout(lay);
        m_mapSizeX = new QSpinBox(this);
        m_mapSizeX->setRange(0,MAP_MAX_SIZE);
        m_mapSizeX->setEnabled(false);
        lay->addWidget(m_mapSizeX);


        m_mapSizeY = new QSpinBox(this);
        m_mapSizeY->setRange(0,MAP_MAX_SIZE);
        m_mapSizeY->setEnabled(false);
        lay->addWidget(m_mapSizeY);
    }
    {
        m_mapNameLabel=new QLabel(this);
        l_mapProperties->addWidget(m_mapNameLabel);
        m_sendingBtn=new QPushButton(tr("(MJ) Envoyer la carte au serveur"), this);
        l_mapProperties->addWidget(m_sendingBtn);
        setSendingButtonEnabled(false);
        connect(m_sendingBtn, SIGNAL(pressed()), this, SLOT(btnMapSend()));
    }
    }

    { ///CASE PROPERTIES DOCK
    QDockWidget* dw_caseProperties = new QDockWidget(tr("Propriétés de la case"), this);
    dw_caseProperties->setWhatsThis(tr("Un dock regroupant quelques propriétés de la case sélectionnée"));
    dw_caseProperties->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dw_caseProperties->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
    QWidget *w_caseProperties = new QWidget(dw_caseProperties);
    dw_caseProperties->setWidget(w_caseProperties);

    addDockWidget(Qt::RightDockWidgetArea, dw_caseProperties);

    QVBoxLayout *l_caseProperties = new QVBoxLayout(w_caseProperties);
    w_caseProperties->setLayout(l_caseProperties);

    {

        m_selectedCaseLabel = new QLabel(this);
        l_caseProperties->addWidget(m_selectedCaseLabel);

        m_selectedCaseRSID = new QSpinBox(this);
        m_selectedCaseRSID->setRange(0,MAX_LOADED_RESSOURCES);
        m_selectedCaseRSID->setEnabled(false);
        l_caseProperties->addWidget(m_selectedCaseRSID);
        connect(m_selectedCaseRSID, SIGNAL(valueChanged(int)), this, SLOT(changeCurrentCaseRSID(int)));

        {
            QGroupBox* gb = new QGroupBox(tr("Objets sur la case :"), this);
            m_mapCaseItemList = new QListWidget(this);
            connect(m_mapCaseItemList, SIGNAL(clicked(const QModelIndex&)), this, SLOT(selectMapItem(const QModelIndex&)));
            m_addItem = new QPushButton(tr("Ajouter un objet"), this);
            m_addItem->setEnabled(false);
            connect(m_addItem, SIGNAL(pressed()), this, SLOT(addMapObject()));
            QVBoxLayout* lyt = new QVBoxLayout();
            gb->setLayout(lyt); lyt->addWidget(m_mapCaseItemList); lyt->addWidget(m_addItem);
            l_caseProperties->addWidget(gb);
        }
    }
    }

    { ///MAPITEMS DOCK
    QDockWidget* dw_mapItems = new QDockWidget(tr("Objets de la carte"), this);
    dw_mapItems->setWhatsThis(tr("Un dock permettant la gestion des objets de la carte"));
    dw_mapItems->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dw_mapItems->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
    QWidget *w_mapItems = new QWidget(dw_mapItems);
    dw_mapItems->setWidget(w_mapItems);

    addDockWidget(Qt::RightDockWidgetArea, dw_mapItems);

    QVBoxLayout *l_mapItems = new QVBoxLayout(w_mapItems);
    w_mapItems->setLayout(l_mapItems);
    {
        m_mapItemList = new QListWidget(this);
        connect(m_mapItemList, SIGNAL(clicked(const QModelIndex&)), this, SLOT(selectMapItem(const QModelIndex&)));
        l_mapItems->addWidget(m_mapItemList);
        m_mapItemName = new QLabel(this);
        l_mapItems->addWidget(m_mapItemName);
        m_mapItemRSID = new QSpinBox(this); m_mapItemRSID->setRange(0,MAX_LOADED_RESSOURCES); m_mapItemRSID->setPrefix(tr("RSID : ")); m_mapItemRSID->setEnabled(false);
        l_mapItems->addWidget(m_mapItemRSID);
        m_mapItemPos = new QLabel(this);
        l_mapItems->addWidget(m_mapItemPos);
        l_mapItems->addWidget(new QLabel(tr("Teinte :"), this));
        m_mapItemColorViewer = new QColorViewer(this);
        l_mapItems->addWidget(m_mapItemColorViewer);
        m_removeItem = new QPushButton(tr("Supprimer l'objet"), this);
        l_mapItems->addWidget(m_removeItem);
        connect(m_removeItem, SIGNAL(pressed()), this, SLOT(removeMapObject()));
    }

    }

    { ///RSSMNGR PROPERTIES DOCK
    QDockWidget* dw_rssMngrProperties = new QDockWidget(tr("Gestionnaire de ressources"), this);
    dw_rssMngrProperties->setWhatsThis(tr("Un dock regroupant les différentes ressources chargées dans l'éditeur"));
    dw_rssMngrProperties->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dw_rssMngrProperties->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
    QWidget *w_rssMngrProperties = new QWidget(dw_rssMngrProperties);
    dw_rssMngrProperties->setWidget(w_rssMngrProperties);

    addDockWidget(Qt::RightDockWidgetArea, dw_rssMngrProperties);
    QVBoxLayout *l_rssMngrProperties = new QVBoxLayout(w_rssMngrProperties);
    w_rssMngrProperties->setLayout(l_rssMngrProperties);
    {
        m_rsMngrFilter = new QLineEdit(this); m_rsMngrFilter->setPlaceholderText(tr("Filtre..."));
        connect(m_rsMngrFilter, SIGNAL(textEdited(const QString&)),this, SLOT(changeRsMngrFilter(const QString&)));
        l_rssMngrProperties->addWidget(m_rsMngrFilter);

        m_rsMngrWidget = new QTableWidget(0,2, this);
        m_rsMngrWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_rsMngrWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        m_rsMngrWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        m_rsMngrWidget->setSortingEnabled(true);
        m_rsMngrWidget->verticalHeader()->hide();
        l_rssMngrProperties->addWidget(m_rsMngrWidget);

        m_rsMngrEdit = new QPushButton(tr("Modifier..."), this);
        m_rsMngrEdit->setEnabled(false);
        l_rssMngrProperties->addWidget(m_rsMngrEdit);

        connect(m_rsMngrEdit, SIGNAL(pressed()), this, SLOT(modifyRssMngr()));

        m_rsMngrAdd = new QPushButton(tr("Ajouter..."), this);
        m_rsMngrAdd->setEnabled(false);
        l_rssMngrProperties->addWidget(m_rsMngrAdd);

        connect(m_rsMngrAdd, SIGNAL(pressed()), this, SLOT(addRssMngr()));
    }
    }

    QMenu *fileMenu = menuBar()->addMenu(tr("&Fichier"));

    QAction *ac_new= fileMenu->addAction(tr("&Nouvelle carte..."));
    connect(ac_new, SIGNAL(triggered()), this, SLOT(newMap()));

    QAction *ac_open= fileMenu->addAction(tr("&Charger une carte..."));
    connect(ac_open, SIGNAL(triggered()), this, SLOT(loadMap()));

    QAction *ac_save = fileMenu->addAction(tr("Sauvegarder &la carte..."));
    connect(ac_save, SIGNAL(triggered()), this, SLOT(saveMap()));

    QAction *ac_saveAs = fileMenu->addAction(tr("Sa&uvegarder la carte sous..."));
    connect(ac_saveAs, SIGNAL(triggered()), this, SLOT(saveMapAs()));

    QAction *ac_quit = fileMenu->addAction(tr("&Quitter..."));
    connect(ac_quit, SIGNAL(triggered()), this, SLOT(close()));


    QMenu *toolMenu = menuBar()->addMenu(tr("&Outils"));
    QAction *ac_replace= toolMenu->addAction(tr("&Remplacer..."));
    connect(ac_replace, SIGNAL(triggered()), this, SLOT(replaceRSID()));
    QAction *ac_copy= toolMenu->addAction(tr("Copier...")); ac_copy->setShortcut(QKeySequence::Copy);
    connect(ac_copy, SIGNAL(triggered()), this, SLOT(copy()));
    QAction *ac_paste= toolMenu->addAction(tr("Coller...")); ac_paste->setShortcut(QKeySequence::Paste);
    connect(ac_paste, SIGNAL(triggered()), this, SLOT(paste()));

    QMenu *exportMenu = menuBar()->addMenu(tr("&Export"));
    QAction *ac_ex_rss= exportMenu->addAction(tr("... la liste de ressources"));
    connect(ac_ex_rss,SIGNAL(triggered()),this,SLOT(exportRss()));
    QAction *ac_ex_map= exportMenu->addAction(tr("... la matrice de la carte"));
    connect(ac_ex_map,SIGNAL(triggered()),this,SLOT(exportMap()));


    m_hoveredCaseLabel = new QLabel(this);
    statusBar()->addWidget(m_hoveredCaseLabel);

    m_mapName=map;
    m_ressourcePackName=ressourceList;
    if(!map.isEmpty())
    {
        loadMap(map,m_ressourcePackName);
    }

    enableMapSystem(false);
}

void MapEditor::setSendingButtonEnabled(bool b) {m_sendingBtn->setEnabled(b);}
bool MapEditor::isSendingButtonEnabled() {return m_sendingBtn->isEnabled();}

void MapEditor::closeEvent (QCloseEvent *ev)
{
    if(saveCheck())
    {
        ev->ignore();
        return;
    }

    delete m_mapWidget;
    m_mapWidget=NULL;
    emit closed();
}

bool MapEditor::isMapValid() const
{
    return m_mapWidget!=NULL&&m_mapWidget->isMapValid()&&!m_mapName.isEmpty();
}

bool MapEditor::replaceRSID()
{
    if(!isMapValid())
        return true;
    bool ok = false;
    RSID from = QInputDialog::getInt(this, tr("Remplacer"), tr("Valeur à changer :"), 0, 0, std::numeric_limits<int>::max()-1, 1, &ok);
    if(!ok)
        return true;

    RSID to = QInputDialog::getInt(this, tr("Remplacer"), tr("Valeur de remplacement :"), 0, 0, std::numeric_limits<int>::max()-1, 1, &ok);
    if(!ok)
        return true;
    if(replaceRSID(from, to))
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'effectuer le remplacement."));
        return true;
    }
    return false;
}

bool MapEditor::replaceRSID(RSID before, RSID after)
{
    if(!isMapValid())
        return true;

    modified();

    MapInformations* map = m_mapWidget->m_map.get();
    for(int xi=0,mx=map->mapSizeX();xi<mx;++xi)
    {
        for(int yi=0,my=map->mapSizeY();yi<my;++yi)
        {
            if(map->map[xi][yi]==before)
                map->map[xi][yi]=after;
        }
    }

    return false;
}

bool MapEditor::saveCheck()
{
    if(!needSave())
        return false;

    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Attention"), tr("Tout travail non sauvegardé sera perdu.\nQue faire ?"), QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
    if(ret == QMessageBox::Cancel)
        return true;

    if(ret == QMessageBox::Discard)
        return false;

    if(ret == QMessageBox::Save)
        return saveMap();

    return true;
}

bool MapEditor::saveRessourcePack()
{
    return saveRessourcePackAs(m_ressourcePackName);
}

bool MapEditor::saveRessourcePackAs(QString fileName)
{
    if(!isMapValid())
        return true;

    if(fileName.isEmpty())
        fileName = QFileDialog::getSaveFileName(this, tr("Sauvegarder un pack de ressources..."),"./Ressources/",tr("Fichiers de liste de ressources (*.list);;Tous les fichiers (*.*)"));

    if(fileName.isEmpty())
        return true;

    return m_mapWidget->saveRessources(fileName);
}

bool MapEditor::saveMap()
{
    return saveMapAs(m_mapName);
}

bool MapEditor::saveMapAs(QString fileName)
{
    if(!isMapValid())
        return true;

    if(fileName.isEmpty())
        fileName = QFileDialog::getSaveFileName(this, tr("Sauvegarder une carte..."),"./Maps/",tr("Fichiers de carte (*.map);;Tous les fichiers (*.*)"));

    if(fileName.isEmpty())
        return true;

    if(m_mapWidget->saveMap(fileName))
        return true;

    m_mapName=fileName;

    return false;
}

bool MapEditor::needSave() const
{
    return m_needSave&&isMapValid();
}

void MapEditor::btnMapSend()
{
    if(isMapValid())
        emit mapSendingRequested(m_mapWidget->getMap(), m_mapWidget->loadedRessources());
}


void MapEditor::changeCasePos(QPoint newCase) //Hovered
{
    if(!isMapValid())
        return;
    m_hoveredCaseLabel->setText(tr("Case : (%1;%2)").arg(newCase.x()).arg(newCase.y()));
}

void MapEditor::changeCurrentCase(QPoint newCase) //Selected
{
    if(!isMapValid())
        return;
    m_selectedCase=newCase;
    m_selectedCaseLabel->setText(tr("Case : (%1;%2)").arg(newCase.x()).arg(newCase.y()));
    m_selectedCaseRSID->setValue(m_mapWidget->m_map->map[newCase.x()][newCase.y()]);
    refreshMapObjectsList(newCase);
}

void MapEditor::addMapObject()
{
    if(!isMapValid())
        return;

    AddObjectDialog dia(this, m_selectedCase, QPoint(m_mapWidget->m_map->mapSizeX(), m_mapWidget->m_map->mapSizeY()), tr("Nouvel objet"));
    if(dia.exec()==QDialog::Accepted)
    {
        m_mapWidget->m_map->mapItems.append(MapItem(dia.getCoords(), dia.getRSID(), dia.getText(), dia.getColor(), static_cast<qreal>(dia.getColorValue())/100.0f));
        refreshObjetsList();
    }
}

bool MapEditor::removeMapObject()
{
    QList<MapItem>& itms = m_mapWidget->m_map->mapItems;

    if(itms.size()<=m_currentItemIndex||m_currentItemIndex<0)
        return true;

    itms.removeAt(m_currentItemIndex);
    if(m_currentItemIndex==itms.size()&&m_currentItemIndex>0)
        --m_currentItemIndex;

    selectMapItem(0);
    refreshObjetsList();
    modified();

    return false;
}

void MapEditor::refreshObjetsList()
{
    if(!isMapValid())
        return;
    refreshMapObjectsList(m_selectedCase);
    refreshGlobalObjetsList();
}

bool MapEditor::selectMapItem(const QModelIndex& index)
{
    QListWidget* lwid = static_cast<QListWidget*>(this->sender());
    if(lwid == 0)
        return true;

    QListWidgetItem* it=lwid->item(index.row());
    if(it == 0)
        return true;

    bool ok=false;
    int ind = it->data(Qt::UserRole).toInt(&ok);
    if(!ok)
        return true;

    return selectMapItem(ind);
}


bool MapEditor::selectMapItem(int index)
{
    if(index<0 || !isMapValid())
        return true;

    const QList<MapItem>& itms = m_mapWidget->m_map->mapItems;

    if(index>=itms.size())
    {
        if(index>0)
            return true;

        m_currentItemIndex=index;
        m_mapItemRSID->setValue(0);
        m_mapItemName->setText(tr("Aucun objet sélectionné"));
        m_mapItemColorViewer->setColor(QColor(0,0,0,0));
        m_mapItemPos->setText(tr("Coordonnées : N/A"));

        return false;
    }

    const MapItem* it= &itms[index];

    m_currentItemIndex=index;
    m_mapItemRSID->setValue(it->rsid);
    m_mapItemName->setText(tr("Nom : \"%1\"").arg(it->text));
    m_mapItemColorViewer->setColor(it->color);
    m_mapItemPos->setText(tr("Coordonnées : (%1;%2)").arg(it->coords.x()).arg(it->coords.y()));

    return false;
}

void MapEditor::refreshGlobalObjetsList()
{
    const QList<MapItem>& itms = m_mapWidget->m_map->mapItems;
    m_mapItemList->clear();
    for(int i=0, m=itms.size(); i<m; ++i)
    {
        QString txt;
        if(!itms[i].text.isEmpty())
            txt=tr("%1 (RSID : %2)").arg(itms[i].text).arg(itms[i].rsid);
        else
            txt=tr("RSID : %1").arg(itms[i].rsid);

        QListWidgetItem* it = new QListWidgetItem(txt);
        it->setData(Qt::UserRole, i);
        m_mapItemList->addItem(it);
    }
}

void MapEditor::refreshMapObjectsList(QPoint newCase)
{
    const QList<MapItem>& itms = m_mapWidget->m_map->mapItems;

    m_mapCaseItemList->clear();

    for(int i=0, m=itms.size(); i<m; ++i)
    {
        if(itms[i].coords==newCase)
        {
            QString txt;
            if(!itms[i].text.isEmpty())
                txt=tr("%1 (RSID : %2)").arg(itms[i].text).arg(itms[i].rsid);
            else
                txt=tr("RSID : %1").arg(itms[i].rsid);

            QListWidgetItem* it = new QListWidgetItem(txt);
            it->setData(Qt::UserRole, i);
            m_mapCaseItemList->addItem(it);
        }
    }
}

void MapEditor::changeCurrentCaseRSID(int n)
{
    if(!isMapValid())
        return;

    if(m_mapWidget->m_map->map[m_selectedCase.x()][ m_selectedCase.y()]!=static_cast<RSID>(n))
    {
        m_mapWidget->m_map->map[m_selectedCase.x()][ m_selectedCase.y()] = static_cast<RSID>(n);
        modified();
    }
}

void MapEditor::modified()
{
    m_needSave=true;
    if(isMapValid())
    {
        setWindowTitle(tr("%1 (modifiée) - Editeur de carte", "1 i the map name").arg(m_mapName));
    }
    else
        setWindowTitle(tr("Editeur de carte"));
}

void MapEditor::unmodified()
{
    m_needSave=false;
    if(isMapValid())
    {
        setWindowTitle(tr("%1 - Editeur de carte", "1 i the map name").arg(m_mapName));
    }
    else
        setWindowTitle(tr("Editeur de carte"));
}

void MapEditor::addRssMngr()
{

    forever
    {
        RSIDDialog dia (this);

        if(!dia.newLine())
            return;
        if(m_mapWidget->isRSIDUsed(dia.getRSID()))
        {
            QMessageBox::critical(this, tr("Erreur"), tr("Le RSID \"%1\" est déjà utilisé.").arg(dia.getRSID()));
            continue;
        }

        if(!m_mapWidget->loadRessource(dia.getName(), dia.getRSID()))
        {
            updateRessourcesList();
            modified();
            return;
        }
        else
        {
            QMessageBox::StandardButton ret; RSID rsid = m_mapWidget->ressourceRSID(dia.getName());
            if(rsid != 0)
            {
                ret = QMessageBox::critical(this, tr("Erreur"), tr("Le fichier \"%1\" est déjà chargé (RSID %2).").arg(dia.getName()).arg(rsid), QMessageBox::Ok|QMessageBox::Abort);
            }
            else
            {
                ret = QMessageBox::critical(this, tr("Erreur"), tr("Le fichier \"%1\" n'a pas pu être chargé.").arg(dia.getName()), QMessageBox::Ok|QMessageBox::Abort);
            }

            if(ret==QMessageBox::Abort)
                return;
        }
    }
}

void MapEditor::modifyRssMngr()
{
    int row=m_rsMngrWidget->currentRow();

    forever
    {
        RSIDDialog dia (this);
        RSID id=m_rsMngrWidget->item(row,0)->data(Qt::UserRole+1).toUInt();
        if(!dia.changeLine(id, m_rsMngrWidget->item(row,1)->text()))
            return;

        if(!m_mapWidget->loadRessource(dia.getName(), id))
        {
            updateRessourcesList();
            modified();
            return;
        }
        else
        {
            QMessageBox::StandardButton ret; RSID rsid = m_mapWidget->ressourceRSID(dia.getName());
            if(rsid != 0)
            {
                ret = QMessageBox::critical(this, tr("Erreur"), tr("Le fichier \"%1\" est déjà charge (RSID %2).").arg(dia.getName()).arg(rsid), QMessageBox::Ok|QMessageBox::Abort);
            }
            else
            {
                ret = QMessageBox::critical(this, tr("Erreur"), tr("Le fichier \"%1\" n'a pas pu être chargé.").arg(dia.getName()), QMessageBox::Ok|QMessageBox::Abort);
            }

            if(ret==QMessageBox::Abort)
                return;
        }
    }
}

void MapEditor::changeSelectedArea(MapArea newArea)
{
    m_selectedArea=newArea;
}

void MapEditor::changeRsMngrFilter(const QString& filter)
{
    m_rsRegExp.setPattern('*'+filter+'*');

    if(!m_rsRegExp.isValid()||m_rsRegExp.isEmpty())
        m_rsRegExp.setPattern("*");

    updateRessourcesList();
}

void MapEditor::updateRessourcesList()
{
    if(!isMapValid())
        return;

    const QMap<QString, RSID>& mp = m_mapWidget->m_loadedRessourcesName;

    QRegExp val = m_rsRegExp;
    if(!val.isValid()||val.isEmpty())
        val.setPattern("*");

    m_rsMngrWidget->clearContents(); m_rsMngrWidget->setRowCount(0); int row=0;
    m_rsMngrWidget->setSortingEnabled(false);
    QMap<QString, RSID>::const_iterator i = mp.constBegin();
    while (i != mp.constEnd())
    {
        if(val.exactMatch(i.key()))
        {
            m_rsMngrWidget->insertRow(row);
            QTableWidgetItem *t=new QTableWidgetItem(); t->setData(Qt::DisplayRole, i.value()); t->setTextAlignment(Qt::AlignHCenter); t->setData(Qt::UserRole+1, i.value());
            m_rsMngrWidget->setItem(row, 0, t);
            m_rsMngrWidget->setItem(row, 1, new QTableWidgetItem(i.key()));
            ++row;
        }

        ++i;
    }
    m_rsMngrWidget->setSortingEnabled(true);
}

void MapEditor::resetCopy()
{
    m_copyArea=MapArea();
    m_copyReady=false;
}

void MapEditor::copy()
{
    m_copyArea=m_selectedArea;
    m_copyReady=true;
}

void MapEditor::paste(QPoint p)
{
    if(!m_copyReady || !isMapValid())
        return;

    modified();
    int sizeX=m_mapWidget->m_map->mapSizeX(); int sizeY=m_mapWidget->m_map->mapSizeY();

    QPoint cas = m_copyArea.size();

    for(int xi=0; xi<cas.x() && xi+p.x()<sizeX; ++xi)
    {
        for(int yi=0; yi<cas.y() && yi+p.y()<sizeY; ++yi)
        {
            m_mapWidget->m_map->map[xi+p.x()][yi+p.y()] = m_mapWidget->m_map->map[m_copyArea.leftUp.x()+xi][m_copyArea.leftUp.y()+yi];
        }
    }

}

void MapEditor::paste()
{
    paste(m_selectedCase);
}

void MapEditor::enableMapSystem(bool b)
{
    m_selectedCaseRSID->setEnabled(b);
    m_rsMngrEdit->setEnabled(b);
    m_rsMngrAdd->setEnabled(b);
    m_addItem->setEnabled(b);

    changeCurrentCase(QPoint(0,0));
    changeCasePos(QPoint(0,0));

    if(b&&isMapValid())
    {
        m_mapSizeX->setValue(m_mapWidget->getMap()->mapSizeX()); m_mapSizeY->setValue(m_mapWidget->getMap()->mapSizeY());

        connect(m_mapWidget, SIGNAL(highlightedCaseChanged(QPoint)), this, SLOT(changeCasePos(QPoint)));

        connect(m_mapWidget, SIGNAL(mapClicked(QPoint)), this, SLOT(changeCurrentCase(QPoint)));
        connect(m_mapWidget, SIGNAL(mapAreaSelected(MapArea)), this, SLOT(changeSelectedArea(MapArea)));

        m_mapNameLabel->setText(tr("Nom de la carte : %1").arg(m_mapName));
    }
    else
    {
        m_mapSizeX->setValue(0); m_mapSizeY->setValue(0);
        m_mapNameLabel->setText(tr("Aucune carte chargée"));
    }

    updateRessourcesList();
    unmodified();
    refreshObjetsList();
    resetCopy();
}

bool MapEditor::loadMap(QString mapName, QString ressPack)
{
    saveCheck();

    if(mapName.isEmpty())
        mapName = QFileDialog::getOpenFileName(this, tr("Charger une carte..."),"./Maps/",tr("Fichiers de carte (*.map);;Tous les fichiers (*.*)"));

    if(mapName.isEmpty())
        return true;

    pgrdia->show();
    pgrdia->setValue(1);

    MapPtr map(new MapInformations); QMap<QString, RSID> rss;
    if(MapWidget::loadCompressedMap(mapName, *map, rss))
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Impossible de charger la carte \"%1\".").arg(mapName));
        pgrdia->setValue(100);
        return true;
    }



    delete m_mapWidget;
    m_mapWidget = new MapWidget(this, 60.0f);
    setCentralWidget(m_mapWidget);

    connect(m_mapWidget, SIGNAL(ressourceLoadingProgress(int,int)), this, SLOT(ressourceLoadingProgress(int,int)));

    m_mapWidget->setHighlight(true);
    m_mapWidget->setMultiSelectionEnabled(true);
    m_mapWidget->setCursor(Qt::CrossCursor);

    pgrdia->setValue(2);

    m_mapWidget->updateRessources(rss);

    pgrdia->setValue(99);

    m_mapWidget->setMap(map);


    disconnect(m_mapWidget, SIGNAL(ressourceLoadingProgress(int,int)), this, SLOT(ressourceLoadingProgress(int,int)));

    m_mapName=mapName;
    m_ressourcePackName=ressPack;
    enableMapSystem(true);

    pgrdia->setValue(100);

    return false;
}

void MapEditor::ressourceLoadingProgress(int curr, int max)
{
    pgrdia->setValue(2+(97*curr/max));
}

bool MapEditor::createEmptyMap(QPoint sizei, const QString& name, const QString& ressPack, RSID defaultRSID)
{
    delete m_mapWidget;
    m_mapWidget = new MapWidget(this, 1.0f);
    setCentralWidget(m_mapWidget);

    m_mapWidget->setHighlight(true);
    m_mapWidget->setMultiSelectionEnabled(true);
    m_mapWidget->setCursor(Qt::CrossCursor);

    m_mapWidget->setMap(MapWidget::makeMap(sizei, defaultRSID));
    if(!m_mapWidget->isMapValid())
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Impossible de créer la carte de dimension %1x%2").arg(sizei.x(), sizei.y()));
        return true;
    }

    m_mapWidget->m_map->name=name;

    if(m_mapWidget->loadRessourcesPack(ressPack).isEmpty())
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Impossible de charger le set d'image \"%1\".").arg(ressPack));
        return true;
    }

    m_mapName=name;

    enableMapSystem(true);
    modified();

    return false;
}

bool MapEditor::makeMap(const QString& name, const QString& mapFile, const QString& ressPack)
{
    delete m_mapWidget;
    m_mapWidget = new MapWidget(this, 1.0f);
    setCentralWidget(m_mapWidget);

    m_mapWidget->setHighlight(true);
    m_mapWidget->setMultiSelectionEnabled(true);
    m_mapWidget->setCursor(Qt::CrossCursor);

    m_mapWidget->setMap(MapWidget::loadMap(mapFile));
    if(!m_mapWidget->isMapValid())
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Impossible de charger le fichier \"%1\"").arg(mapFile));
        return true;
    }

    m_mapWidget->m_map->name=name;

    if(m_mapWidget->loadRessourcesPack(ressPack).isEmpty())
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Impossible de charger le set d'image \"%1\".").arg(ressPack));
        return true;
    }

    m_mapName=name;

    enableMapSystem(true);
    modified();

    return false;
}

bool MapEditor::newMap()
{
    saveCheck();
    NewMapDialog dia(this);
    if(!dia.exec())
        return true;

    if(dia.isEmptyMap())
        return createEmptyMap(dia.getSize(), dia.getName(), dia.getRessourceList(), dia.getRSID());

    return makeMap(dia.getName(), dia.getMapFile(), dia.getRessourceList());
}

bool MapEditor::exportMap()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Exporter une matrice..."),"./Maps/",tr("Fichiers de matrices (*.rawmap);;Tous les fichiers (*.*)"));
    if(file.isEmpty())
        return true;

    return m_mapWidget->saveMapMatrix(file);
}

bool MapEditor::exportRss()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Exporter un pack de ressources..."),"./Ressources/",tr("Fichiers de ressources (*.list);;Tous les fichiers (*.*)"));
    if(file.isEmpty())
        return true;
    return m_mapWidget->saveRessources(file);;
}
