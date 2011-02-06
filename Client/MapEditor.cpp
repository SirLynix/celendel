#include "MapEditor.h"
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QDockWidget>
#include <QLayout>
#include <QDebug>
#include <QSpinBox>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>

class RSIDDialog : public QDialog
{
    public:

    RSIDDialog(QWidget* parent) : QDialog(parent), m_used(false)
    {
        m_spinBox=new QSpinBox(this);
        m_lineEdit=new QLineEdit(this);
        m_lineEdit->setPlaceholderText(tr("Fichier de ressource..."));
        QHBoxLayout* l=new QHBoxLayout();
        l->addWidget(m_spinBox);
        m_spinBox->setMaximum(MAX_LOADED_RESSOURCES);
        m_spinBox->setPrefix(tr("RSID : "));
        l->addWidget(m_lineEdit);

        QVBoxLayout* vl=new QVBoxLayout();
        vl->addLayout(l);

        m_accept = new QPushButton(tr("Valider"), this);
        connect(m_accept, SIGNAL(pressed()), this, SLOT(accept()));
        m_cancel = new QPushButton(tr("Retour"), this);
        connect(m_cancel, SIGNAL(pressed()), this, SLOT(reject()));

        QHBoxLayout* h=new QHBoxLayout();
        h->addWidget(m_accept);
        h->addWidget(m_cancel);
        vl->addLayout(h);

        setLayout(vl);

    }

    int newLine()
    {
        if(m_used)
            return 0;

        m_used=true;

        return exec();
    }

    int changeLine(RSID id, const QString& name = QString())
    {
        if(m_used)
            return 0;

        m_used=true;

        m_spinBox->setValue(id);
        m_spinBox->setEnabled(false);
        m_lineEdit->setText(name);

        return exec();
    }


    RSID getRSID() const { return m_spinBox->value(); }
    QString getName() const {  return m_lineEdit->text(); }

    private:

    bool m_used;

    QSpinBox* m_spinBox;
    QLineEdit* m_lineEdit;
    QPushButton* m_accept;
    QPushButton* m_cancel;

};

MapEditor::MapEditor(QWidget* parent, const QString& map, const QString& ressourceList):QMainWindow(parent)
{
    m_mapWidgetScroll = NULL;
    unmodified();

    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);
    setDockNestingEnabled(true);

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
    QAction *ac_open= fileMenu->addAction(tr("&Charger une carte..."));
    connect(ac_open, SIGNAL(triggered()), this, SLOT(loadMap()));

    QAction *ac_save = fileMenu->addAction(tr("Sauvegarder &la carte..."));
    connect(ac_save, SIGNAL(triggered()), this, SLOT(saveMap()));

    QAction *ac_saveAs = fileMenu->addAction(tr("Sa&uvegarder la carte sous..."));
    connect(ac_saveAs, SIGNAL(triggered()), this, SLOT(saveMapAs()));

    QAction *ac_saveAll = fileMenu->addAction(tr("Tout &sauvegarder..."));
    connect(ac_saveAll, SIGNAL(triggered()), this, SLOT(saveAll()));

    QAction *ac_saveAllAs = fileMenu->addAction(tr("Tout sauveg&arder sous..."));
    connect(ac_saveAllAs, SIGNAL(triggered()), this, SLOT(saveAllAs()));

    QAction *ac_quit = fileMenu->addAction(tr("&Quitter..."));
    connect(ac_quit, SIGNAL(triggered()), this, SLOT(close()));


    QMenu *toolMenu = menuBar()->addMenu(tr("&Outils"));
    QAction *ac_replace= toolMenu->addAction(tr("&Remplacer..."));
    connect(ac_replace, SIGNAL(triggered()), this, SLOT(replaceRSID()));

    m_hoveredCaseLabel = new QLabel(this);
    statusBar()->addWidget(m_hoveredCaseLabel);

    m_mapName=map;
    m_ressourcePackName=ressourceList;
    if(!map.isEmpty())
    {
        loadMap(map,m_ressourcePackName);
    }

}

void MapEditor::setSendingButtonEnabled(bool b) {m_sendingBtn->setEnabled(b);}
bool MapEditor::isSendingButtonEnabled() {return m_sendingBtn->isEnabled();}

void MapEditor::closeEvent (QCloseEvent *event)
{
    saveCheck();

    delete m_mapWidgetScroll;
    m_mapWidgetScroll=NULL;
}

bool MapEditor::isMapValid() const
{
    return m_mapWidgetScroll!=NULL&&m_mapWidgetScroll->getMapWidget()->isMapValid()&&!m_mapName.isEmpty();
}

bool MapEditor::replaceRSID()
{
    if(!isMapValid())
        return true;

}

bool MapEditor::replaceRSID(RSID before, RSID after)
{
    if(!isMapValid())
        return true;

    MapInformations* map = m_mapWidgetScroll->getMapWidget()->m_map.get();
    for(int x=0,mx=map->mapSizeX();x<mx;++x)
    {
        for(int y=0,my=map->mapSizeY();y<my;++y)
        {
            if(map->map[x][y]==before)
                map->map[x][y]=after;
        }
    }

    return false;
}

bool MapEditor::saveCheck()
{
    if(!needSave())
        return false;

    QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Attention"), tr("Tout travail non sauvegardé sera perdu.\nQue faire ?"), QMessageBox::Save|QMessageBox::SaveAll|QMessageBox::Discard|QMessageBox::Cancel);
    if(ret == QMessageBox::Cancel)
        return true;

    if(ret == QMessageBox::Discard)
        return false;

    if(ret == QMessageBox::SaveAll)
        return saveMap()||saveRessourcePack();

    if(ret == QMessageBox::Save)
        return saveMap();

    return true;
}

bool MapEditor::saveAll()
{
    return saveAllAs(m_mapName, m_ressourcePackName);
}

bool MapEditor::saveAllAs(QString mapName, QString ressName)
{
    if(!isMapValid())
        return true;

    return saveMapAs(mapName)||saveRessourcePackAs(ressName);
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
        fileName = QFileDialog::getSaveFileName(this, tr("Sauvegarder un pack de ressources..."),QString(),tr("Fichiers de liste de ressources (*.list);;Tous les fichiers (*.*)"));

    if(fileName.isEmpty())
        return true;

    return m_mapWidgetScroll->getMapWidget()->saveRessources(fileName);
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
        fileName = QFileDialog::getSaveFileName(this, tr("Sauvegarder une carte..."),QString(),tr("Fichiers de carte (*.map);;Tous les fichiers (*.*)"));

    if(fileName.isEmpty())
        return true;

    if(m_mapWidgetScroll->getMapWidget()->saveMap(fileName))
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
        emit mapSendingRequested(m_mapWidgetScroll->getMapWidget()->getMap());
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
    m_selectedCaseRSID->setValue(m_mapWidgetScroll->getMapWidget()->m_map->map[newCase.x()][newCase.y()]);
}

void MapEditor::changeCurrentCaseRSID(int n)
{
    if(!isMapValid())
        return;

    m_mapWidgetScroll->getMapWidget()->m_map->map[m_selectedCase.x()][ m_selectedCase.y()] = (RSID)n;
    modified();
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
        if(m_mapWidgetScroll->getMapWidget()->isRSIDUsed(dia.getRSID()))
        {
            QMessageBox::critical(this, tr("Erreur"), tr("Le RSID \"%1\" est déjà utilisé.").arg(dia.getRSID()));
            continue;
        }

        if(!m_mapWidgetScroll->getMapWidget()->loadRessource(dia.getName(), dia.getRSID()))
        {
            updateRessourcesList();
            modified();
            return;
        }
        else
        {
            QMessageBox::StandardButton ret; RSID rsid = m_mapWidgetScroll->getMapWidget()->ressourceRSID(dia.getName());
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

        if(!m_mapWidgetScroll->getMapWidget()->loadRessource(dia.getName(), id))
        {
            updateRessourcesList();
            modified();
            return;
        }
        else
        {
            QMessageBox::StandardButton ret; RSID rsid = m_mapWidgetScroll->getMapWidget()->ressourceRSID(dia.getName());
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

void MapEditor::updateRessourcesList()
{
    if(!isMapValid())
        return;

    const QMap<QString, RSID>& mp = m_mapWidgetScroll->getMapWidget()->m_loadedRessourcesName;

    m_rsMngrWidget->clearContents(); m_rsMngrWidget->setRowCount(0); int row=0;
    m_rsMngrWidget->setSortingEnabled(false);
    QMap<QString, RSID>::const_iterator i = mp.constBegin();
    while (i != mp.constEnd())
    {
        m_rsMngrWidget->insertRow(row);
        QTableWidgetItem *t=new QTableWidgetItem(QString::number(i.value())); t->setTextAlignment(Qt::AlignHCenter); t->setData(Qt::UserRole+1, i.value());
        m_rsMngrWidget->setItem(row, 0, t);
        m_rsMngrWidget->setItem(row, 1, new QTableWidgetItem(i.key()));

        ++i; ++row;
    }
    m_rsMngrWidget->setSortingEnabled(true);
}

bool MapEditor::loadMap(QString mapName, QString ressPack)
{
    saveCheck();

    if(mapName.isEmpty())
        mapName = QFileDialog::getOpenFileName(this, tr("Charger une carte..."),QString(),tr("Fichiers de carte (*.map);;Tous les fichiers (*.*)"));

    if(mapName.isEmpty())
        return true;

    if(ressPack.isEmpty())
        ressPack = QFileDialog::getOpenFileName(this, tr("Charger un pack de ressources..."),QString(), tr("Fichiers de liste (*.list);;Tous les fichiers (*.*)"));

    delete m_mapWidgetScroll;
    m_mapWidgetScroll = new MapWidgetScroll(this);
    setCentralWidget(m_mapWidgetScroll);

    MapWidget* mapRender = m_mapWidgetScroll->getMapWidget();
    mapRender->setHighlight(true);
    mapRender->setCursor(Qt::CrossCursor);
    if(mapRender->loadRessourcesPack(ressPack).isEmpty()||mapRender->setMap(mapName))
    {
        QMessageBox::critical(this,tr("Erreur"),tr("Impossible de charger la carte \"%1\" ou le set d'image \"%2\".").arg(mapName).arg(ressPack));
        return true;
    }

    m_mapName=mapName;
    m_ressourcePackName=ressPack;
    m_mapSizeX->setValue(mapRender->getMap()->mapSizeX());
    m_mapSizeY->setValue(mapRender->getMap()->mapSizeY());

    connect(mapRender, SIGNAL(highlightedCaseChanged(QPoint)), this, SLOT(changeCasePos(QPoint)));
    changeCasePos(QPoint(0,0));

    connect(mapRender, SIGNAL(mapClicked(QPoint)), this, SLOT(changeCurrentCase(QPoint)));
    changeCurrentCase(QPoint(0,0));

    m_mapNameLabel->setText(tr("Nom de la carte : %1").arg(m_mapName));

    m_selectedCaseRSID->setEnabled(true);
    m_rsMngrEdit->setEnabled(true);
    m_rsMngrAdd->setEnabled(true);

    updateRessourcesList();
    unmodified();

    return false;
}
