#include "ClientInterface.h"
#include "..\Shared\Serializer.h"

ClientInterface::ClientInterface()
{
    m_mapWi=new QWidget(this); ///Debug
    m_mapWi->setMinimumSize(200,200);

    setCentralWidget(m_mapWi);

    #include "GUI.cpp"

    m_ID=0;
    m_gameStarted=false;

    m_network=new ClientNetwork(this);
    connect(m_network, SIGNAL(chatReceived(CLID, QString, ENUM_TYPE)), this, SLOT(chat(CLID, QString, ENUM_TYPE )));
    connect(m_network, SIGNAL(serverInformationsChanged(ServerInformations)), this, SLOT(changeServerInformations(ServerInformations)));
    connect(m_network, SIGNAL(clientIDChanged(CLID)), this, SLOT(changeClientID(CLID)));
    connect(m_network, SIGNAL(nicknameChanged(CLID, QString)), this, SLOT(changeClientNickname(CLID, QString)));
}

void ClientInterface::sendMessage()
{
    if(!m_network->isConnected())
    {
        return;
    }
    m_network->send(ETI(CHAT), serialiseChatData(ETI(NORMAL), m_chatInput->text(), 0));
    m_chatInput->setText("");
}

void ClientInterface::changeClientNickname(CLID ID, QString nick)
{
    if(m_nickMap.value(ID)!="")
    {
        m_chat->append(tr("%1 s'appelle maintenant %2 (ID %3).").arg(m_nickMap.value(ID)).arg(nick).arg(ID));
    }
    else
    {
        m_chat->append(tr("Le client anonyme ID %1 s'appelle maintenant %2.").arg(ID).arg(nick));
    }
    m_nickMap[ID]=nick;

}

void ClientInterface::changeClientID(CLID ID)
{
    m_ID=ID;
}

void ClientInterface::changeServerInformations(ServerInformations si)
{
    m_GMID=si.gameMasterID;
    m_location=si.location;
    m_TOD=si.timeOfDay;
    m_serverName=si.serverName;
    m_nickMap=si.playersName;
    m_gameStarted=si.gameStarted;
}

void ClientInterface::chat(CLID sender, QString text, ENUM_TYPE canal)
{
    if(canal==NORMAL)
    {
        m_chat->append(m_nickMap.value(sender)+"["+QString::number(sender)+"] : "+text);
    }
}
