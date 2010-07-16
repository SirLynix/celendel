  /*         buildGui() : build the client GUI          */
 /* This function in ClientInterface constructor only. */
/*         Workers :
                - Gigotdarnaud                        */

#include "ClientInterface.h"

void ClientInterface::buildGUI()
{
  ////////////////////////////
 /// MENUS FEATURES BELOW ///
////////////////////////////

// FILE MENU
QMenu *fileMenu = menuBar()->addMenu(tr("&Fichier"));
QAction *ac_save = fileMenu->addAction(tr("&Sauvegarder la partie"));
ac_save->setShortcut(QKeySequence(QKeySequence::Save));
QAction *ac_load = fileMenu->addAction(tr("Charger une partie"));
ac_load->setShortcut(QKeySequence(QKeySequence::Open));
m_ac_joinOrLeave = fileMenu->addAction(tr("Se connecter au serveur")); //This text will change, depending if the client is connected or not.
connect(m_ac_joinOrLeave, SIGNAL(triggered()), this, SLOT(switchConnectionState()));
QAction *ac_quit = fileMenu->addAction(tr("&Quitter"));
ac_quit->setShortcut(QKeySequence(QKeySequence::Quit));
connect(ac_quit, SIGNAL(triggered()), qApp, SLOT(quit()));

// SETTINGS MENU
QMenu *settingsMenu = menuBar()->addMenu(tr("&Paramètres"));
QAction *ac_settings = settingsMenu->addAction(tr("Options"));
ac_settings->setShortcut(QKeySequence(QKeySequence::Preferences));
connect(ac_settings, SIGNAL(triggered()), this, SLOT(openSettings()));
QAction *ac_sounds = settingsMenu->addAction(tr("Parcourir les sons"));
connect(ac_sounds, SIGNAL(triggered()), this, SLOT(openSoundsGUI()));

// ABOUT MENU
QMenu *aboutMenu = menuBar()->addMenu(tr("&A propos..."));
QAction *ac_aboutServer = aboutMenu->addAction(tr("... du serveur"));
connect(ac_aboutServer, SIGNAL(triggered()), this, SLOT(aboutServer()));

QAction *ac_aboutUs = aboutMenu->addAction(tr("... de Celendel"));
connect(ac_aboutUs, SIGNAL(triggered()), this, SLOT(aboutUs()));

QAction *ac_aboutQt = aboutMenu->addAction(tr("... de Qt"));
connect(ac_aboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));


// CONTEXTUAL MENUS
m_kick = new QAction(tr("Ejecter le joueur"), this);
connect(m_kick, SIGNAL(triggered()), this, SLOT(actionKick()));
m_ban = new QAction(tr("Bannir le joueur"), this);
connect(m_ban, SIGNAL(triggered()), this, SLOT(actionBan()));
m_voteGM = new QAction(tr("Elire Maître du Jeu"), this);
connect(m_voteGM, SIGNAL(triggered()), this, SLOT(actionVoteGM()));
m_changeGM = new QAction(tr("Changer de Maître du Jeu"), this);
connect(m_changeGM, SIGNAL(triggered()), this, SLOT(actionChangeGM()));

  ////////////////////////////
 /// DOCKS FEATURES BELOW ///
////////////////////////////

QWidget* m_centralWi=new QWidget(this);

m_centralWi->setMinimumSize(0,0);
m_centralWi->setMaximumSize(1,1);

setCentralWidget(m_centralWi);

resize(1024,768);
setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);
setDockNestingEnabled(true);

///MAIN CHAT DOCK
QDockWidget *chatDock = new QDockWidget(tr("Chat"), this);
chatDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
chatDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
QWidget *w_chatDock = new QWidget(chatDock);
chatDock->setWidget(w_chatDock);
QVBoxLayout *l_chatDock = new QVBoxLayout(w_chatDock);
w_chatDock->setLayout(l_chatDock);

m_chat = new QTextEdit(this);
m_chat->setReadOnly(true);
l_chatDock->addWidget(m_chat);

addDockWidget(Qt::RightDockWidgetArea, chatDock);

///NARRATOR DOCK
QDockWidget *narratorDock = new QDockWidget(tr("Narrateur"), this);
narratorDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
narratorDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
QWidget *w_narratorDock = new QWidget(narratorDock);
narratorDock->setWidget(w_narratorDock);
QVBoxLayout *l_narratorDock = new QVBoxLayout(w_narratorDock);
w_narratorDock->setLayout(l_narratorDock);

m_narrator = new QTextEdit(this);
m_narrator->setReadOnly(true);
l_narratorDock->addWidget(m_narrator);

addDockWidget(Qt::RightDockWidgetArea, narratorDock);

tabifyDockWidget(chatDock, narratorDock);


///RP CHAT DOCK
QDockWidget *RPChatDock = new QDockWidget(tr("Jeu de rôle"), this);
RPChatDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
RPChatDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
QWidget *w_RPChatDock = new QWidget(RPChatDock);
RPChatDock->setWidget(w_RPChatDock);
QVBoxLayout *l_RPChatDock = new QVBoxLayout(w_RPChatDock);
w_RPChatDock->setLayout(l_RPChatDock);

m_RPChat = new QTextEdit(this);
m_RPChat->setReadOnly(true);
l_RPChatDock->addWidget(m_RPChat);

addDockWidget(Qt::RightDockWidgetArea, RPChatDock);

tabifyDockWidget(chatDock, RPChatDock);

///CHAT INPUT DOCK
QDockWidget *chatInputDock = new QDockWidget(tr("Commandes"), this);
chatInputDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
chatInputDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
QWidget *w_chatInputDock = new QWidget(chatInputDock);
chatInputDock->setWidget(w_chatInputDock);
QVBoxLayout *l_chatInputDock = new QVBoxLayout(w_chatInputDock);
w_chatInputDock->setLayout(l_chatInputDock);

m_chatInput = new QLineEdit(this);
l_chatInputDock->addWidget(m_chatInput);
connect(m_chatInput, SIGNAL(returnPressed()), this, SLOT(sendMessage()));

m_rollTheDice = new QPushButton(tr("Roll 1d20"), this);
l_chatInputDock->addWidget(m_rollTheDice);
connect(m_rollTheDice, SIGNAL(pressed()), this, SLOT(rollDice()));

addDockWidget(Qt::RightDockWidgetArea, chatInputDock);

w_chatInputDock->setMaximumHeight(m_chatInput->height()+m_rollTheDice->height()*3/2);


///PLAYER LIST DOCK
QDockWidget *playerListDock = new QDockWidget(tr("Liste des joueurs"), this);
playerListDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
playerListDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
m_playerList = new QStandardItemModel(this);

QWidget *w_playerListDock = new QWidget(playerListDock);
playerListDock->setWidget(w_playerListDock);
QVBoxLayout *l_playerListDock = new QVBoxLayout(w_playerListDock);
w_playerListDock->setLayout(l_playerListDock);

m_v_pl = new QTreeView(this);
m_v_pl->setModel(m_playerList);
m_v_pl->header()->hide();
m_v_pl->setEditTriggers(QAbstractItemView::NoEditTriggers);
m_v_pl->setContextMenuPolicy(Qt::CustomContextMenu);
connect(m_v_pl, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(playerListMenu(const QPoint&)));
l_playerListDock->addWidget(m_v_pl);

m_GMLabel=new QLabel(this);
l_playerListDock->addWidget(m_GMLabel);

playerListDock->setWidget(w_playerListDock);

addDockWidget(Qt::LeftDockWidgetArea, playerListDock);


///character LIST DOCK
QDockWidget *characterListDock = new QDockWidget(tr("Liste des personnages"), this);
characterListDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
characterListDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
m_characterList = new QStandardItemModel(this);

QWidget *w_characterListDock = new QWidget(characterListDock);
characterListDock->setWidget(w_characterListDock);
QVBoxLayout *l_characterListDock = new QVBoxLayout(w_characterListDock);
w_characterListDock->setLayout(l_characterListDock);

{
QTreeView *v = new QTreeView(this);
v->setModel(m_characterList);
v->header()->hide();
v->setEditTriggers(QAbstractItemView::NoEditTriggers);
l_characterListDock->addWidget(v);
}


characterListDock->setWidget(w_characterListDock);

addDockWidget(Qt::LeftDockWidgetArea, characterListDock);

m_centralWi->setMaximumSize(1,1);
}
