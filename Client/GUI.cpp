  /*           buildGui() : build the client GUI            */
 /* Use this function in ClientInterface constructor only. */


#include "ClientInterface.h"
#include "MapWidget.h"
#include "ScriptManager.h"
#include "EntitiesManager.h"
#include "CharactersManager.h"

#define ON(a) a->setObjectName(#a)

void ClientInterface::buildGUI()
{
  ////////////////////////////
 /// MENUS FEATURES BELOW ///
////////////////////////////

// FILE MENU
QMenu *fileMenu = menuBar()->addMenu(tr("&Fichier"));
QAction *ac_save = fileMenu->addAction(tr("&Sauvegarder la partie"));
ac_save->setWhatsThis(tr("Sauvegarder les param�tres, le jeu de r�le et les discutions de la partie."));
ac_save->setShortcut(QKeySequence(QKeySequence::Save));
connect(ac_save, SIGNAL(triggered()), this, SLOT(saveGame()));
QAction *ac_load = fileMenu->addAction(tr("Charger une partie"));
connect(ac_load, SIGNAL(triggered()), this, SLOT(loadGame()));
ac_load->setWhatsThis(tr("Charger les param�tres, le jeu de r�le et les discutions d'une partie. �videment, il n'est pas possible de re-connecter les autres clients, ni de r�initialiser le server. Vous serez par ailleurs d�connect�."));
ac_load->setShortcut(QKeySequence(QKeySequence::Open));
m_ac_joinOrLeave = fileMenu->addAction(tr("Se connecter au serveur")); //This text will change, depending if the client is connected or not.
connect(m_ac_joinOrLeave, SIGNAL(triggered()), this, SLOT(switchConnectionState()));
m_ac_joinOrLeave->setWhatsThis(tr("Se connecter ou se d�connecter du serveur (IP et port indiqu�s dans les options)."));
QAction *ac_quit = fileMenu->addAction(tr("&Quitter"));
ac_quit->setWhatsThis(tr("Quitter honteusement la partie."));
ac_quit->setShortcut(QKeySequence(QKeySequence::Quit));
connect(ac_quit, SIGNAL(triggered()), qApp, SLOT(quit()));

// SETTINGS MENU
QMenu *settingsMenu = menuBar()->addMenu(tr("&Param�tres"));
QAction *ac_settings = settingsMenu->addAction(tr("Options"));
ac_settings->setWhatsThis(tr("Adjuster quelques param�tres et diverses options."));
ac_settings->setShortcut(QKeySequence(QKeySequence::Preferences));
connect(ac_settings, SIGNAL(triggered()), this, SLOT(openSettings()));
QAction *ac_sounds = settingsMenu->addAction(tr("Parcourir les sons"));
ac_sounds->setWhatsThis(tr("Explorer les biblioth�ques de sons charg�es."));
connect(ac_sounds, SIGNAL(triggered()), this, SLOT(openSoundsGUI()));

// RENDERING MENU
QMenu *renderingMenu = menuBar()->addMenu(tr("&Module de rendu"));
QAction *ac_mapInformations = renderingMenu->addAction(tr("Informations sur la carte"));
ac_mapInformations->setWhatsThis(tr("Affiche quelques informations tr�s interessantes sur la carte. Vraiment."));
connect(ac_mapInformations, SIGNAL(triggered()), m_mapWi, SLOT(openMapInfoDialog()));
QAction *ac_mapEditor = renderingMenu->addAction(tr("Ouvrir l'�diteur de cartes"));
ac_mapEditor->setWhatsThis(tr("Ouvre l'�diteur de carte. Utile comme aide, n'est-ce pas ?"));
connect(ac_mapEditor, SIGNAL(triggered()), this, SLOT(openMapEditor()));

// ABOUT MENU
QMenu *aboutMenu = menuBar()->addMenu(tr("&A propos..."));
QAction *ac_aboutServer = aboutMenu->addAction(tr("... du serveur"));
ac_aboutServer->setWhatsThis(tr("Afficher le Mot du Jour du serveur."));
connect(ac_aboutServer, SIGNAL(triggered()), this, SLOT(aboutServer()));

QAction *ac_aboutUs = aboutMenu->addAction(tr("... de Celendel"));
ac_aboutUs->setWhatsThis(tr("Afficher quelques informations � propos de ce merveilleux logiciel et de ses non moins g�niaux cr�ateurs."));
connect(ac_aboutUs, SIGNAL(triggered()), this, SLOT(aboutUs()));

QAction *ac_aboutQt = aboutMenu->addAction(tr("... de Qt"));
ac_aboutQt->setWhatsThis(tr("Afficher quelques informations � propos du framework C++ open-source multi-licences Qt (� Nokia, tous droits r�serv�s) utilis� massivement pour la cr�ation de Celendel."));
connect(ac_aboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

// CONTEXTUAL MENUS
m_kick = new QAction(tr("Ejecter le joueur"), this);
m_kick->setWhatsThis(tr("D�connecter m�chament le joueur du serveur."));
connect(m_kick, SIGNAL(triggered()), this, SLOT(actionKick()));
m_ban = new QAction(tr("Bannir le joueur"), this);
m_ban->setWhatsThis(tr("PARS, ET NE REVIENS JAMAAAAAAIS !")); // What ? I write the eastern eggs I want !
connect(m_ban, SIGNAL(triggered()), this, SLOT(actionBan()));
m_voteGM = new QAction(tr("�lire Ma�tre du Jeu"), this);
m_voteGM->setWhatsThis(tr("Votez pour moi !"));
connect(m_voteGM, SIGNAL(triggered()), this, SLOT(actionVoteGM()));
m_changeGM = new QAction(tr("Changer de Ma�tre du Jeu"), this);
m_changeGM->setWhatsThis(tr("Abandonner l�chement ses fonctions et ses pouvoirs surhumains au profit d'un autre."));
connect(m_changeGM, SIGNAL(triggered()), this, SLOT(actionChangeGM()));
m_separator = new QAction(this); m_separator->setSeparator(true);
m_VOIPDisconnect = new QAction(tr("VOIP : Se d�connecter de ce client"), this);
m_VOIPDisconnect->setWhatsThis(tr("VOIP : Si vous vous d�connectez d'un client, vous ne lui enverez plus de message audio, et vous ne recevrez plus les siens."));
connect(m_VOIPDisconnect, SIGNAL(triggered()), this, SLOT(VOIPRemoveClient()));
m_VOIPConnect = new QAction(tr("VOIP : Rajouter ce client au module"), this);
m_VOIPConnect->setWhatsThis(tr("VOIP : Si vous ajoutez un client au module VOIP, vous recevrez ses messages audio, et vous pourrez lui en envoyer � votre tour."));
connect(m_VOIPConnect, SIGNAL(triggered()), this, SLOT(VOIPAddClient()));
m_VOIPVolume = new QAction(tr("VOIP : R�gler le volume de r�ception"), this);
m_VOIPVolume->setWhatsThis(tr("VOIP : Modifier le volume de r�ception du client. Cela n'affectera pas les autres clients."));
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

///MAP DOCK
QDockWidget *mapDock = new QDockWidget(tr("Carte"), this);
ON(mapDock);
mapDock->setWhatsThis(tr("Le dock de la carte"));
mapDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
mapDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);

QWidget *w_mapDock = new QWidget(mapDock);
mapDock->setWidget(w_mapDock);
QVBoxLayout *l_mapDock = new QVBoxLayout(w_mapDock);
w_mapDock->setLayout(l_mapDock);


l_mapDock->addWidget(m_mapWi);

m_flare = new QPushButton(tr("Montrer"), this);
connect(m_flare, SIGNAL(pressed()),this,SLOT(mapFlare()));
l_mapDock->addWidget(m_flare);

addDockWidget(Qt::TopDockWidgetArea, mapDock);

///MAIN CHAT DOCK
QDockWidget *chatDock = new QDockWidget(tr("Chat"), this);
ON(chatDock);
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
ON(narratorDock);
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
QDockWidget *RPChatDock = new QDockWidget(tr("Jeu de r�le"), this);
ON(RPChatDock);
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
ON(chatInputDock);
chatInputDock->setWhatsThis(tr("Le dock des commandes"));
chatInputDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
chatInputDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
QWidget *w_chatInputDock = new QWidget(chatInputDock);
chatInputDock->setWidget(w_chatInputDock);
QVBoxLayout *l_chatInputDock = new QVBoxLayout(w_chatInputDock);
w_chatInputDock->setLayout(l_chatInputDock);

m_RPLanguage = new QComboBox(this);
m_RPLanguage->setWhatsThis(tr("Selectionnez le langage de la r�plique du personnage."));
l_chatInputDock->addWidget(m_RPLanguage);

m_chatInput = new QLineEdit(this);
m_chatInput->setWhatsThis(tr("Entrez ici commandes et dialogues."));
l_chatInputDock->addWidget(m_chatInput);
connect(m_chatInput, SIGNAL(returnPressed()), this, SLOT(sendMessage()));

{
QHBoxLayout *yahourt = new QHBoxLayout;
m_rollTheDice = new QPushButton(tr("Roll 1d20"), this);
m_rollTheDice->setWhatsThis(tr("Lancer 1d20. Un d� � vingt faces, quoi..."));
yahourt->addWidget(m_rollTheDice);
connect(m_rollTheDice, SIGNAL(released()), this, SLOT(rollDice()));

m_rollSpecialDice = new QPushButton(tr("Lancer un autre d�..."), this);
m_rollSpecialDice->setWhatsThis(tr("Pour les lanceurs de d�s les plus exigents !"));
yahourt->addWidget(m_rollSpecialDice);
connect(m_rollSpecialDice, SIGNAL(released()), this, SLOT(rollSpecialDice()));


l_chatInputDock->addLayout(yahourt);
}

addDockWidget(Qt::RightDockWidgetArea, chatInputDock);

w_chatInputDock->setMaximumHeight(m_RPLanguage->height() + m_chatInput->height()+m_rollTheDice->height());


///PLAYER LIST DOCK
QDockWidget *playerListDock = new QDockWidget(tr("Liste des joueurs"), this);
ON(playerListDock);
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

///SCRIPTS DOCK
QDockWidget *scriptsDock = new QDockWidget(tr("Scripts"), this);
ON(scriptsDock);
scriptsDock->setWhatsThis(tr("Gestion des scripts"));
scriptsDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
scriptsDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);

m_scriptManager = new ScriptManager(scriptsDock);
scriptsDock->setWidget(m_scriptManager);

addDockWidget(Qt::LeftDockWidgetArea, scriptsDock);

///ENTITIES DOCK
QDockWidget *entitiesDock = new QDockWidget(tr("Entit�es script�es"), this);
ON(entitiesDock);
entitiesDock->setWhatsThis(tr("Gestion des entit�es (objets, personnages...)"));
entitiesDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
entitiesDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);

m_entitiesManager = new EntitiesManager(entitiesDock);
entitiesDock->setWidget(m_entitiesManager);

addDockWidget(Qt::LeftDockWidgetArea, entitiesDock);

tabifyDockWidget(scriptsDock, entitiesDock);


///CHARACTER LIST DOCK
QDockWidget *characterListDock = new QDockWidget(tr("Liste des personnages"), this);
ON(characterListDock);
characterListDock->setWhatsThis(tr("La liste des personnages"));
characterListDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
characterListDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);

m_characterMngr = new CharactersManager(m_entitiesManager, characterListDock);
characterListDock->setWidget(m_characterMngr);

addDockWidget(Qt::LeftDockWidgetArea, characterListDock);

///GM PANEL LIST DOCK
m_GMPanelDock = new QDockWidget(tr("Panneau d'administration"), this);
m_GMPanelDock->setObjectName("GMPanelDock");
m_GMPanelDock->setWhatsThis(tr("Le panneau d'administration"));
m_GMPanelDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
m_GMPanelDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);

QTabWidget *GMPanelTab = new QTabWidget(m_GMPanelDock);
m_GMPanelDock->setWidget(GMPanelTab);

{
QGroupBox* gb=new QGroupBox(tr("Langages"),this);
GMPanelTab->addTab(gb, tr("Langages"));
QVBoxLayout* layouti=new QVBoxLayout(gb);
m_languageManagement = new QTableWidget(0,2,this);
m_languageManagement->setContextMenuPolicy(Qt::CustomContextMenu);
{QStringList _tmp; _tmp<<tr("Langage")<<tr("Dictionnaire", "For the multi-language system"); m_languageManagement->setHorizontalHeaderLabels(_tmp); }
m_languageManagement->setEditTriggers(QAbstractItemView::NoEditTriggers);
m_languageManagement->setSelectionMode(QAbstractItemView::SingleSelection);
layouti->addWidget(m_languageManagement);

m_addLanguage = new QPushButton(tr("Ajouter un langage"), this);
connect(m_addLanguage, SIGNAL(pressed()), this, SLOT(addLanguage()));
layouti->addWidget(m_addLanguage);

m_importLanguages = new QPushButton(tr("Importer une liste de langages"), this);
connect(m_importLanguages, SIGNAL(pressed()), this, SLOT(importLanguageList()));
layouti->addWidget(m_importLanguages);

m_syncroniseLanguages = new QPushButton(tr("Synchroniser la liste des langages"), this);
connect(m_syncroniseLanguages, SIGNAL(pressed()), this, SLOT(sendLanguageList()));
layouti->addWidget(m_syncroniseLanguages);
}

{
QGroupBox* gb=new QGroupBox(tr("Dictionnaires"),this);
GMPanelTab->addTab(gb, tr("Dictionnaires"));

QVBoxLayout* layouti=new QVBoxLayout(gb);
m_dictionnariesList = new QListWidget(this);
layouti->addWidget(m_dictionnariesList);

m_addDictionnary = new QPushButton(tr("Ajouter un dictionnaire"), this);
layouti->addWidget(m_addDictionnary);
connect(m_addDictionnary, SIGNAL(pressed()), this, SLOT(addDictionnary()));
}

connect(m_languageManagement, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(languageListMenu(const QPoint&)));
m_removeLanguage = new QAction(tr("Supprimer le langage"), this);
connect(m_removeLanguage, SIGNAL(triggered()), this, SLOT(removeLanguageMenu()));
m_addLanguageAct = new QAction(tr("Ajouter un langage"), this);
connect(m_addLanguageAct, SIGNAL(triggered()), this, SLOT(addLanguage()));


addDockWidget(Qt::LeftDockWidgetArea, m_GMPanelDock);

m_GMPanelDock->hide();

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
