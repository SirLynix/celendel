
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
l_chatDock->addWidget(m_chat);

addDockWidget(Qt::RightDockWidgetArea, chatDock);

///NARRATOR DOCK
QDockWidget *narratorDock = new QDockWidget(tr("Narrator"), this);
narratorDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
narratorDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
QWidget *w_narratorDock = new QWidget(narratorDock);
narratorDock->setWidget(w_narratorDock);
QVBoxLayout *l_narratorDock = new QVBoxLayout(w_narratorDock);
w_narratorDock->setLayout(l_narratorDock);

m_narrator = new QTextEdit(this);
l_narratorDock->addWidget(m_narrator);

addDockWidget(Qt::RightDockWidgetArea, narratorDock);


///RP CHAT DOCK
QDockWidget *RPChatDock = new QDockWidget(tr("Chat RP"), this);
RPChatDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
RPChatDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
QWidget *w_RPChatDock = new QWidget(RPChatDock);
RPChatDock->setWidget(w_RPChatDock);
QVBoxLayout *l_RPChatDock = new QVBoxLayout(w_RPChatDock);
w_RPChatDock->setLayout(l_RPChatDock);

m_RPChat = new QTextEdit(this);
l_RPChatDock->addWidget(m_RPChat);

addDockWidget(Qt::RightDockWidgetArea, RPChatDock);

///CHAT INPUT DOCK
QDockWidget *chatInputDock = new QDockWidget(tr("chatInput"), this);
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

addDockWidget(Qt::RightDockWidgetArea, chatInputDock);

