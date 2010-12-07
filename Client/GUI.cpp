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
ac_save->setWhatsThis(tr("Sauvegarder les paramètres, le jeu de rôle et les discutions de la partie."));
ac_save->setShortcut(QKeySequence(QKeySequence::Save));
connect(ac_save, SIGNAL(triggered()), this, SLOT(saveGame()));
QAction *ac_load = fileMenu->addAction(tr("Charger une partie"));
connect(ac_load, SIGNAL(triggered()), this, SLOT(loadGame()));
ac_load->setWhatsThis(tr("Charger les paramètres, le jeu de rôle et les discutions d'une partie. Évidement, il n'est pas possible de re-connecter les autres clients, ni de réinitialiser le server. Vous serez par ailleurs déconnecté."));
ac_load->setShortcut(QKeySequence(QKeySequence::Open));
m_ac_joinOrLeave = fileMenu->addAction(tr("Se connecter au serveur")); //This text will change, depending if the client is connected or not.
connect(m_ac_joinOrLeave, SIGNAL(triggered()), this, SLOT(switchConnectionState()));
m_ac_joinOrLeave->setWhatsThis(tr("Se connecter ou se déconnecter du serveur (IP et port indiqués dans les options)."));
QAction *ac_quit = fileMenu->addAction(tr("&Quitter"));
ac_quit->setWhatsThis(tr("Quitter honteusement la partie."));
ac_quit->setShortcut(QKeySequence(QKeySequence::Quit));
connect(ac_quit, SIGNAL(triggered()), qApp, SLOT(quit()));

// SETTINGS MENU
QMenu *settingsMenu = menuBar()->addMenu(tr("&Paramètres"));
QAction *ac_settings = settingsMenu->addAction(tr("Options"));
ac_settings->setWhatsThis(tr("Adjuster quelques paramètres et diverses options."));
ac_settings->setShortcut(QKeySequence(QKeySequence::Preferences));
connect(ac_settings, SIGNAL(triggered()), this, SLOT(openSettings()));
QAction *ac_sounds = settingsMenu->addAction(tr("Parcourir les sons"));
ac_sounds->setWhatsThis(tr("Explorer les bibliothèques de sons chargées."));
connect(ac_sounds, SIGNAL(triggered()), this, SLOT(openSoundsGUI()));

// ABOUT MENU
QMenu *aboutMenu = menuBar()->addMenu(tr("&A propos..."));
QAction *ac_aboutServer = aboutMenu->addAction(tr("... du serveur"));
ac_aboutServer->setWhatsThis(tr("Afficher le Mot du Jour du serveur."));
connect(ac_aboutServer, SIGNAL(triggered()), this, SLOT(aboutServer()));

QAction *ac_aboutUs = aboutMenu->addAction(tr("... de Celendel"));
ac_aboutUs->setWhatsThis(tr("Afficher quelques informations à propos de ce merveilleux logiciel et de ses non moins géniaux créateurs."));
connect(ac_aboutUs, SIGNAL(triggered()), this, SLOT(aboutUs()));

QAction *ac_aboutQt = aboutMenu->addAction(tr("... de Qt"));
ac_aboutQt->setWhatsThis(tr("Afficher quelques informations à propos du framework C++ open-source multi-licences Qt (© Nokia, tous droits réservés) utilisé massivement pour la création de Celendel."));
connect(ac_aboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));


// CONTEXTUAL MENUS
m_kick = new QAction(tr("Ejecter le joueur"), this);
m_kick->setWhatsThis(tr("Déconnecter méchament le joueur du serveur."));
connect(m_kick, SIGNAL(triggered()), this, SLOT(actionKick()));
m_ban = new QAction(tr("Bannir le joueur"), this);
m_ban->setWhatsThis(tr("PARS, ET NE REVIENS JAMAAAAAAIS !")); // What ? I write the eastern eggs I want !
connect(m_ban, SIGNAL(triggered()), this, SLOT(actionBan()));
m_voteGM = new QAction(tr("Élire Maître du Jeu"), this);
m_voteGM->setWhatsThis(tr("Votez pour moi !"));
connect(m_voteGM, SIGNAL(triggered()), this, SLOT(actionVoteGM()));
m_changeGM = new QAction(tr("Changer de Maître du Jeu"), this);
m_changeGM->setWhatsThis(tr("Abandonner lâchement ses fonctions et ses pouvoirs surhumains au profit d'un autre."));
connect(m_changeGM, SIGNAL(triggered()), this, SLOT(actionChangeGM()));
m_separator = new QAction(this); m_separator->setSeparator(true);
m_VOIPDisconnect = new QAction(tr("VOIP : Se déconnecter de ce client"), this);
m_VOIPDisconnect->setWhatsThis(tr("VOIP : Si vous vous déconnectez d'un client, vous ne lui enverez plus de message audio, et vous ne recevrez plus les siens."));
connect(m_VOIPDisconnect, SIGNAL(triggered()), this, SLOT(VOIPRemoveClient()));
m_VOIPConnect = new QAction(tr("VOIP : Rajouter ce client au module"), this);
m_VOIPConnect->setWhatsThis(tr("VOIP : Si vous ajoutez un client au module VOIP, vous recevrez ses messages audio, et vous pourrez lui en envoyer à votre tour."));
connect(m_VOIPConnect, SIGNAL(triggered()), this, SLOT(VOIPAddClient()));
m_VOIPVolume = new QAction(tr("VOIP : Régler le volume de réception"), this);
m_VOIPVolume->setWhatsThis(tr("VOIP : Modifier le volume de réception du client. Cela n'affectera pas les autres clients."));
connect(m_VOIPVolume, SIGNAL(triggered()), this, SLOT(VOIPClientVolume()));

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
chatDock->setWhatsThis(tr("Le dock du chat (hors jeu)"));
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
narratorDock->setWhatsThis(tr("Le dock du narrateur"));
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
RPChatDock->setWhatsThis(tr("Le dock des dialogues du jeu."));
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
chatInputDock->setWhatsThis(tr("Le dock des commandes"));
chatInputDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
chatInputDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
QWidget *w_chatInputDock = new QWidget(chatInputDock);
chatInputDock->setWidget(w_chatInputDock);
QVBoxLayout *l_chatInputDock = new QVBoxLayout(w_chatInputDock);
w_chatInputDock->setLayout(l_chatInputDock);

m_RPLanguage = new QComboBox(this);
m_RPLanguage->setWhatsThis(tr("Selectionnez le langage de la réplique du personnage."));
l_chatInputDock->addWidget(m_RPLanguage);

m_chatInput = new QLineEdit(this);
m_chatInput->setWhatsThis(tr("Entrez ici commandes et dialogues."));
l_chatInputDock->addWidget(m_chatInput);
connect(m_chatInput, SIGNAL(returnPressed()), this, SLOT(sendMessage()));

m_rollTheDice = new QPushButton(tr("Roll 1d20"), this);
m_rollTheDice->setWhatsThis(tr("Lancer 1d20. Un dé à vingt faces, quoi..."));
l_chatInputDock->addWidget(m_rollTheDice);
connect(m_rollTheDice, SIGNAL(pressed()), this, SLOT(rollDice()));

addDockWidget(Qt::RightDockWidgetArea, chatInputDock);

w_chatInputDock->setMaximumHeight(m_RPLanguage->height() + m_chatInput->height()+m_rollTheDice->height());


///PLAYER LIST DOCK
QDockWidget *playerListDock = new QDockWidget(tr("Liste des joueurs"), this);
playerListDock->setWhatsThis(tr("La liste des joueurs"));
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


///CHARACTER LIST DOCK
QDockWidget *characterListDock = new QDockWidget(tr("Liste des personnages"), this);
characterListDock->setWhatsThis(tr("La liste des personnages"));
characterListDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
characterListDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
m_characterList = new QStandardItemModel(this);


QWidget *w_characterListDock = new QWidget(characterListDock);
characterListDock->setWidget(w_characterListDock);
QVBoxLayout *l_characterListDock = new QVBoxLayout(w_characterListDock);
w_characterListDock->setLayout(l_characterListDock);


m_v_cl = new QTreeView(this);
m_v_cl->setModel(m_characterList);
m_v_cl->header()->hide();
m_v_cl->setEditTriggers(QAbstractItemView::NoEditTriggers);
m_v_cl->setContextMenuPolicy(Qt::CustomContextMenu);
connect(m_v_cl, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(characterListMenu(const QPoint&)));
l_characterListDock->addWidget(m_v_cl);

addDockWidget(Qt::LeftDockWidgetArea, characterListDock);


///GM PANEL LIST DOCK
QDockWidget *GMPanelDock = new QDockWidget(tr("Panneau d'administration"), this);
GMPanelDock->setWhatsThis(tr("Le panneau d'administration"));
GMPanelDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
GMPanelDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);

QWidget *w_GMPanelDock = new QWidget(GMPanelDock);
GMPanelDock->setWidget(w_GMPanelDock);
QVBoxLayout *l_GMPanelDock = new QVBoxLayout(w_GMPanelDock);
w_GMPanelDock->setLayout(l_GMPanelDock);

addDockWidget(Qt::LeftDockWidgetArea, GMPanelDock);


m_centralWi->setMaximumSize(1,1);

///Status bar
QStatusBar *bar = statusBar();
m_dlPerSec = new QLabel(this);
m_dlPerSec->setText(tr("Download :     0 o/s"));
m_dlPerSec->setEnabled(false);
bar->addWidget(m_dlPerSec);
m_upPerSec = new QLabel(this);
m_upPerSec->setText(tr("Upload :     0 o/s"));
m_upPerSec->setEnabled(false);
bar->addWidget(m_upPerSec);
}
