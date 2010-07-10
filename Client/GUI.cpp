
/* This file will be included in ClientInterface constructor. */

resize(1024,768);
setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);

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


///PLAYER LIST DOCK
QDockWidget *playerListDock = new QDockWidget(tr("Liste des joueurs"), this);
playerListDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
playerListDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
m_playerList = new QStandardItemModel(this);

QWidget *w_playerListDock = new QWidget(playerListDock);
playerListDock->setWidget(w_playerListDock);
QVBoxLayout *l_playerListDock = new QVBoxLayout(w_playerListDock);
w_playerListDock->setLayout(l_playerListDock);

QTreeView *v = new QTreeView(this);
v->setModel(m_playerList);
v->header()->hide();
v->setEditTriggers(QAbstractItemView::NoEditTriggers);
l_playerListDock->addWidget(v);

m_GMLabel=new QLabel(this);
l_playerListDock->addWidget(m_GMLabel);

playerListDock->setWidget(w_playerListDock);

addDockWidget(Qt::LeftDockWidgetArea, playerListDock);

