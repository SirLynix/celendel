#include "SoundsGUI.h"
#include "SoundManager.h"
#include "SoundLibThread.h"

#define DTA_LIB Qt::UserRole+75
#define DTA_SOUND DTA_LIB+1

SoundsGUI::SoundsGUI(QWidget* pa):QDialog(pa)
{
    setWindowTitle(tr("Sons"));
    setWhatsThis(tr("Ceci est... euh... une boîte de dialogue."));
    QVBoxLayout *la = new QVBoxLayout(this);
    setLayout(la);

    m_model = new QStandardItemModel(this);
    QStringList libs=sndMngr.loadedLibs();

    d=new dial(this);

    for(int i=0;i<libs.size();++i)
    {
        QStandardItem *item = new QStandardItem(libs[i]);
        item->setData(libs[i], DTA_LIB);
        item->setData("", DTA_SOUND);
        m_model->appendRow(item);
        QStringList sounds=sndMngr.getLibsSounds(libs[i]);
        for(int j=0;j<sounds.size();++j)
        {
            QStandardItem *u=new QStandardItem(sounds[j]);
            u->setData(libs[i], DTA_LIB);
            u->setData(sounds[j], DTA_SOUND);
            item->appendRow(u);
        }
    }


    m_view = new QTreeView(this);
    m_view->setWhatsThis(tr("Ici sont rangés l'ensemble des bibliothèques de sons chargées, ainsi que leur contenu."));
    m_view->setModel(m_model);
    m_view->header()->hide();
    m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_view, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(contextMenu(const QPoint&)));
    la->addWidget(m_view);

    m_a_play=new QAction(tr("Jouer"), this);
    connect(m_a_play, SIGNAL(triggered()), this, SLOT(play()));
    m_a_stop=new QAction(tr("Stop"), this);
    connect(m_a_stop, SIGNAL(triggered()), this, SLOT(stop()));

    m_new=new QPushButton(tr("Créer une bibliothèque..."), this);
    m_new->setWhatsThis(tr("Ouvre une nouvelle boite de dialogue pour créer des banques de sons personnalisées à partie d'un dossier. Formats audio acceptés : OGG Vorbis (conseillé) et fichiers WAV (hautement déconseillés)"));
    la->addWidget(m_new);
    connect(m_new, SIGNAL(pressed()), this, SLOT(createLib()));

    m_back=new QPushButton(tr("Retour"), this);
    m_back->setWhatsThis(tr("Ferme la boîte de dialoque."));
    la->addWidget(m_back);
    connect(m_back, SIGNAL(pressed()), this, SLOT(accept()));
}

void SoundsGUI::contextMenu(const QPoint& p)
{
    QModelIndex mod = m_view->indexAt(p);
    if(!mod.isValid())
        return;

    QString sound=mod.data(DTA_SOUND).toString();
    QString lib=mod.data(DTA_LIB).toString();
    QList<QAction*> list;

    m_a_play->setData(p);
    m_a_stop->setData(p);

    if(!sound.isEmpty())
    {
        list<<m_a_stop;
        list<<m_a_play;
    }

    if(!list.isEmpty())
        QMenu::exec(list, m_view->mapToGlobal(p));
}

void SoundsGUI::play()
{
    QModelIndex mod = m_view->indexAt(m_a_play->data().toPoint());
    if(!mod.isValid())
        return;
    QString sound=mod.data(DTA_SOUND).toString();
    QString lib=mod.data(DTA_LIB).toString();
    sndMngr.playSound(lib, sound);
}

void SoundsGUI::stop()
{
    QModelIndex mod = m_view->indexAt(m_a_play->data().toPoint());
    if(!mod.isValid())
        return;
    QString sound=mod.data(DTA_SOUND).toString();
    QString lib=mod.data(DTA_LIB).toString();
    sndMngr.stopSound(lib, sound);
}

void SoundsGUI::createLib()
{
    bool ok=false;
    QString name = QInputDialog::getText (this, tr("Création d'une bibliothèque de sons"), tr("Nom de la bibliothèque :"), QLineEdit::Normal, tr("MaSuperLib"), &ok);
    if (!ok || name.isEmpty())
         return;
    QString dir = QFileDialog::getExistingDirectory(this, tr("Selectionner le dossier contenant les sons"));
    if(dir.isEmpty())
        return;

    SoundLibThread th(name, dir);
    th.start();
    connect(&th, SIGNAL(finished()), d, SLOT(close()));
    d->exec();
}

dial::dial(QWidget *par):QDialog(par)
{
    setWindowTitle(tr("42 - Don't panic !"));
    QLabel* l=new QLabel(tr("<h3>Copie des données en cours, création de la bibliothèque...</h3>Il est possible que l'opération prenne du temps, tout spécialement si la machine hôte est lente ou que la quantité de données à copier est importante, merci de patienter. Forcer la fermeture provoquerait la corruption des données de la bibliothèque en cours d'écriture."), this);
    l->setWordWrap(true);
    QHBoxLayout *la=new QHBoxLayout;
    setLayout(la);
    la->addWidget(l);

    setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint|Qt::WindowTitleHint);
}
