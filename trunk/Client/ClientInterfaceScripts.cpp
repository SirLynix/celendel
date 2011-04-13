#include "ClientInterface.h"
#include "..\Shared\Serializer.h"


void ClientInterface::scriptToGMMsg(QString ent, QString txt)
{
    lg(tr("<b>GM Script message</b> : [%1] <font color=\"firebrick\">\"%2\"</font>").arg(ent).arg(txt), true, true);
}

void ClientInterface::scriptToOwnerMsg(QString ent, QString txt)
{
    lg(tr("<b>Script message</b> : [%1] <font color=\"firebrick\">\"%2\"</font>").arg(ent).arg(txt), true, true);
}

void ClientInterface::scriptActionMsg(QString ent, QString txt)
{
    lg(tr("<b>Script action</b> : [%1] <font color=\"firebrick\">\"%2\"</font>").arg(ent).arg(txt), true, true);
}

void ClientInterface::scriptToPlayerMsg(QString ent, QString txt)
{
    lg(tr("<b>Script message</b> : [%1] <font color=\"firebrick\">\"%2\"</font>").arg(ent).arg(txt), true, true);
}

void ClientInterface::scriptMsg(QString ent, QString txt)
{
    lg(tr("<b>Script message</b> : [%1] <font color=\"firebrick\">\"%2\"</font>").arg(ent).arg(txt), true, true);
}

void ClientInterface::scriptError(QString ent, QString txt)
{
    lg(tr("<b>Script error</b> : [%1] <font color=\"red\">\"%2\"</font>").arg(ent).arg(txt), true, true);
}


void ClientInterface::makeEntity(QString name, QString scriptName)
{
    if(!isGM())
        return;

    m_network->send(ETI(CREATE_ENTITY), serialiseCreateEntityData(name, scriptName));
}

void ClientInterface::deleteEntity(const QString& name)
{
    if(!isGM())
        return;

    m_network->send(ETI(DELETE_ENTITY), serialiseDeleteEntityData(name));
}

void ClientInterface::sendScriptToServer(QString name, QString content)
{
    if(!isGM())
        return;

    DEB() << "Script " << name << " sent to server...";

    m_network->send(ETI(SEND_SCRIPT), serialiseSendScriptData(name, content));
}

void ClientInterface::requestScriptDownload(QString name)
{
    if(!isConnected())
        return;

    m_network->send(ETI(REQUEST_SCRIPT_UPDATE), serialiseRequestScriptData(name));
}

void ClientInterface::deleteScript(QString name)
{
    if(!isGM())
        return;

    m_network->send(ETI(DELETE_SCRIPT), serialiseDeleteScriptData(name));
}

void ClientInterface::renameScript(QString name, QString newName)
{
    if(!isGM())
        return;

    m_network->send(ETI(RENAME_SCRIPT), serialiseRenameScriptData(name, newName));
}

void ClientInterface::injectCode(QString entityName, QString code)
{
     if(!isGM())
        return;

    m_network->send(ETI(INJECT_CODE), serialiseInjectCodeData(entityName, code));
}
