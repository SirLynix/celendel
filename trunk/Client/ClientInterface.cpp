#include "ClientInterface.h"
#include "..\Shared\Serializer.h"

ClientInterface::ClientInterface()
{
    m_mapWi=new QWidget(this); ///Debug
    m_mapWi->setMinimumSize(200,200);

    setCentralWidget(m_mapWi);

    #include "GUI.cpp"

    m_network=new ClientNetwork(this);
}

void ClientInterface::sendMessage()
{
    if(!m_network->isConnected())
    {
        return;
    }
    m_network->send(ETI(CHAT), serialiseChatData(ETI(NORMAL), m_chatInput->text()));
    m_chatInput->setText("");
}
