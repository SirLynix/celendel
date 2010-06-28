#include "ClientInterface.h"

ClientInterface::ClientInterface()
{
    m_mapWi=new QWidget(this); ///Debug
    m_mapWi->setMinimumSize(200,200);

    setCentralWidget(m_mapWi);

    #include "GUI.cpp"

    m_network=new ClientNetwork(this);
}


