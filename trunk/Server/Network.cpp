#include "Network.h"
#include "Client.h"

#include <QDebug>
#include <QDateTime>
#include <QTextDocument>
#include "..\Shared\Serializer.h"

QString securise (const QString& in)
{
    QString ret=Qt::escape(in.simplified());
    return ret;
}

ServerNetwork::ServerNetwork(quint16 port, QObject* parent) : QObject(parent)
{
    m_server=new QTcpServer(this);
    if(!m_server->listen(QHostAddress::Any, port))
    {
        qDebug() << tr("Error - The server network failed to start. Reason : ") << m_server->errorString();
        //Well, what are we supposed to do now ?
    }
    else
    {
        connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
        log(tr("Server launched on port ") + QString::number(m_server->serverPort()) + tr(" and ready to use."));
    }

    flushTimer=new QTimer(this);

    flushTimer->setSingleShot(false);
    connect(flushTimer, SIGNAL(timeout()), this, SLOT(flush()));
    flushTimer->start(100);
}

ServerNetwork::~ServerNetwork()
{
    for(int i=0; i<m_clients.size(); ++i)
        delete m_clients[i];
}

void ServerNetwork::flush()
{
    for(int i=0;i<m_clients.size();++i)
        m_clients[i]->flush();
}

void ServerNetwork::kick(CLID ID, const QString& reason)
{
    Client *c = getClient(ID);
    if(c==NULL)
        return;

    sendToAll(ETI(GTFO_LYNIX), serialiseGTFOLynixData(ID, ETI(KICK), reason));
    c->socket->disconnectFromHost();
}

void ServerNetwork::ban(CLID ID, const QString& reason)
{
    Client *c = getClient(ID);
    if(c==NULL)
        return;

    m_banList.append(c->socket->peerAddress().toString());
    sendToAll(ETI(GTFO_LYNIX), serialiseGTFOLynixData(ID, ETI(BAN), reason));
    c->socket->disconnectFromHost();
}

int ServerNetwork::unban(const QString& IP)
{
    return m_banList.removeAll(IP);
}

void ServerNetwork::newConnection()
{
    log("Someone connected.");
    Client *newCl = new Client(m_server->nextPendingConnection());

    if(m_clients.size() >= MAX_CLIENTS)
    {
        log("Server full, connection denied !");
        Packet p;
        p.type=ETI(ERROR);
        p.data=serialiseErrorData(ETI(CLIENTS_LIMIT_REACHED));
        newCl->send(p);
        newCl->socket->disconnectFromHost(); //Be polite. Just disconnect, do not abort !
        newCl->deleteLater();
        return;
    }
    else if(m_banList.contains(newCl->socket->peerAddress().toString()))
    {
        log("Client banned, connection denied !");
        Packet p;
        p.type=ETI(GTFO_LYNIX);
        p.data=serialiseGTFOLynixData(0, ETI(BAN));
        newCl->send(p);
        newCl->socket->disconnectFromHost();
        newCl->deleteLater();
        return;
    }

    connect(newCl, SIGNAL(dataReceived(Packet*)), this, SLOT(slot_dataReceived(Packet*)));
    connect(newCl, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    for(int i=0; i<m_clients.size(); ++i)
    {
        if(newCl->ID()==m_clients[i]->ID())
        {
            newCl->changeID();
            i=0;
        }
    }

    log("Client connected with ID " + QString::number(newCl->ID()));
    m_clients.append(newCl);
    emit newClient(newCl->ID());
}

void ServerNetwork::clientDisconnected()
{
    Client *cl = qobject_cast<Client*>(sender());
    if (cl==NULL) //It shouldn't happen. Realy.
        return;

    m_clients.removeOne(cl);
    emit clientGone(cl->ID());
    log("Client (ID " + QString::number(cl->ID()) + ") left");
    cl->deleteLater();
}

Client* ServerNetwork::getClient(CLID cID)
{
    for(int i=0; i<m_clients.size();++i)
    {
        if(m_clients[i]->ID()==cID)
        {
            return m_clients[i];
        }
    }
    log("ERROR : Client "+QString::number(cID)+" not found !");
    return NULL;
}

void ServerNetwork::slot_dataReceived(Packet* packet)
{
    Client *cl = qobject_cast<Client*>(sender());
    if (cl==NULL) //Wait, what ?
    {
        delete packet; //We'll say the packet is lost because of network lag... None shall know what happened.
        return;
    }

    emit dataReceived(packet, cl->ID());
}

bool ServerNetwork::sendToClient(CLID ID, qint32 type, const QByteArray& data, qint32 ts, qint32 pID)
{
    Packet p;
    p.type=type;
    p.timestamp=ts;
    p.data=data;
    if(pID!=-1)
        p.ID=pID;
    return sendToClient(ID, p);
}

void ServerNetwork::sendToAll(qint32 type, const QByteArray& data, qint32 ts, qint32 pID)
{
    Packet p;
    p.type=type;
    p.timestamp=ts;
    p.data=data;
    if(pID!=-1)
        p.ID=pID;
    sendToAll(p);
}

bool ServerNetwork::sendToClient(CLID ID, Packet& pa)
{
    return sendToClient(ID, &pa, false);
}

void ServerNetwork::sendToAll(Packet& pa)
{
    sendToAll(&pa, false);
}

bool ServerNetwork::sendToClient(CLID ID, Packet* pa, bool delegateDelete)
{
    //log("Sending packet to Client " + QString::number(ID) + "...");

    //pa->show(); ///Debug

    int i;
    for(i=0; i<m_clients.size();++i)
    {
        if(m_clients[i]->ID()==ID)//Found !
        {
            m_clients[i]->send(pa);
            if(delegateDelete)
                delete pa;

            return false;
        }
    }
    log("Error : client not found. Packet has been lost.");

    //The client haven't been found.

    if(delegateDelete)
        delete pa;

    return true;
}

void ServerNetwork::sendToAll(Packet* pa, bool delegateDelete)
{
    for(int i=0; i<m_clients.size();++i)
    {
        sendToClient(m_clients[i]->ID(), pa, false);
    }

    if(delegateDelete)
        delete pa;
}

void log(const QString txt, bool time)
{
    QString tmp;
    if(time)
    {
        tmp += QDateTime::currentDateTime().toString("dd/MM/yyyy - HH:mm:ss.zzz") + " : ";
    }
    tmp+=txt;
    qDebug(tmp.toAscii());
}
