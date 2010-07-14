#include "ClientInterface.h"
#include "..\Shared\Serializer.h"

void ClientInterface::buildGMStuff()
{
    m_refreshTimer=new QTimer(this);
    m_refreshTimer->setSingleShot(false);
    m_refreshTimer->start(150);
    connect(m_refreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    m_needRefresh=true;

    connect(m_narrator, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

void ClientInterface::narrationChanged(QString txt)
{
    if(!isGM())
    {
        m_narrator->setHtml(txt);
        m_narrator->moveCursor(QTextCursor::End);
    }
}

void ClientInterface::refresh()
{
    if(!m_needRefresh || !isGM())
        return;

    m_network->send(ETI(ALL_NARRATION), serialiseAllNarrationData(m_narrator->toHtml()));

    m_needRefresh=false;
}

void ClientInterface::textChanged()
{
    m_needRefresh=true;
}
