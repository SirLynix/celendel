#include "ScriptEnvironnement.h"

#include "../Shared/LuaSystem/ScriptedEntity.h"

ScriptEnvironnement::ScriptEnvironnement()
{

}

ScriptEnvironnement::~ScriptEnvironnement()
{
    for(QMap<QString, ScriptedEntity*>::const_iterator i = m_entities.constBegin(); i!=m_entities.constEnd();++i)
    {
        delete i.value();
    }
}

void ScriptEnvironnement::dataChanged()
{
    ScriptedEntity* ent = qobject_cast<ScriptedEntity*>(sender());
    if(ent == 0)
        return;
    QString name = m_entities.key(ent);
    if(name.isEmpty())
        return;

    emit entityRequireUpdate(name);
}

EntityInformations ScriptEnvironnement::getEntityInformations(const QString& name)
{
    EntityInformations ei;

    ScriptedEntity* ent = m_entities.value(name, 0);

    if(ent == 0)
        return ei;

    ei.name = name;
    ei.data = ent->getData();

    QString ply = m_chPlyMap.key(name);
    if(!ply.isEmpty())
        ei.data["player"].setData(ply);
    else
        ei.data.remove("player");

    return ei;
}

QList<EntityInformations> ScriptEnvironnement::getEntitiesInformations()
{
    QList<EntityInformations> list;

    for(QMap<QString, ScriptedEntity*>::const_iterator i = m_entities.constBegin(); i!=m_entities.constEnd();++i)
    {
        list.append(EntityInformations());
        EntityInformations& ei = list.last();
        ei.name = i.key();
        ei.data = i.value()->getData();

        QString ply = m_chPlyMap.key(i.key());

        if(!ply.isEmpty())
            ei.data["player"].setData(ply);
        else
            ei.data.remove("player");
    }

    return list;
}

bool ScriptEnvironnement::makeEntity(const QString& name, const QString& scriptName)
{
    if(m_entities.contains(name))
        return true;

    ScriptedEntity* ent = new ScriptedEntity(scriptName);

    if(!ent->isValid())
    {
        delete ent;
        return true;
    }

    m_entities[name]=ent;

    connect(ent, SIGNAL(luaError(QString)), this, SLOT(s_luaError(QString)));
    connect(ent, SIGNAL(dataChanged()), this, SLOT(dataChanged()));
    connect(ent, SIGNAL(sendGMMsg(QString)), this, SLOT(s_sendGMMsg(QString)));
    connect(ent, SIGNAL(sendOwnerMsg(QString)), this, SLOT(s_sendOwnerMsg(QString)));
    connect(ent, SIGNAL(sendMsg(QString)), this, SLOT(s_sendMsg(QString)));
    connect(ent, SIGNAL(sendPlayerMsg(QString,QString)), this, SLOT(s_sendPlayerMsg(QString,QString)));
    connect(ent, SIGNAL(registerCharacter(QString)), this, SLOT(s_registerCharacter(QString)));

    return false;
}

QString ScriptEnvironnement::pushCode(const QString& entity, const QString& code, bool* b)
{
    bool bp=false;
    if(b == NULL)
        b=&bp;

    ScriptedEntity* ent = m_entities.value(entity, NULL);

    if(ent==NULL)
    {
        *b=false;
        return QString();
    }

    return ent->pushCode(code, b);
}

bool ScriptEnvironnement::deleteEntity(const QString& name)
{
    ScriptedEntity* ent = m_entities.take(name);
    if(ent == 0)
        return true;

    delete ent;

    removeCharacter(name);

    return false;
}

void ScriptEnvironnement::s_luaError(QString m)
{
    ScriptedEntity* ent = qobject_cast<ScriptedEntity*>(sender());
    if(ent == 0)
        return;
    QString name = m_entities.key(ent);
    if(name.isEmpty())
        return;
    emit luaError(name, m);
}

void ScriptEnvironnement::s_sendGMMsg(QString m)
{
    ScriptedEntity* ent = qobject_cast<ScriptedEntity*>(sender());
    if(ent == 0)
        return;
    QString name = m_entities.key(ent);
    if(name.isEmpty())
        return;
    emit sendGMMsg(name,m);
}

void ScriptEnvironnement::s_sendOwnerMsg(QString m)
{
    ScriptedEntity* ent = qobject_cast<ScriptedEntity*>(sender());
    if(ent == 0)
        return;
    QString name = m_entities.key(ent);
    if(name.isEmpty())
        return;
    emit sendOwnerMsg(name,m);
}

void ScriptEnvironnement::s_sendMsg(QString m)
{
    ScriptedEntity* ent = qobject_cast<ScriptedEntity*>(sender());
    if(ent == 0)
        return;
    QString name = m_entities.key(ent);
    if(name.isEmpty())
        return;
    emit sendMsg(name,m);
}

void ScriptEnvironnement::s_sendPlayerMsg(QString msg,QString regexp)
{
    ScriptedEntity* ent = qobject_cast<ScriptedEntity*>(sender());
    if(ent == 0)
        return;
    QString name = m_entities.key(ent);
    if(name.isEmpty())
        return;
    emit sendPlayerMsg(name,msg,regexp);
}

void ScriptEnvironnement::removeCharacter(const QString& ent)
{
    if(!m_characters.removeOne(ent))
        return;

    m_chPlyMap.remove(m_chPlyMap.key(ent));

    emit characterListUpdated(m_characters);
}

void ScriptEnvironnement::addCharacter(const QString& name, const QString& ply)
{
    if(!m_characters.contains(name))
    {
        m_characters.append(name);
        emit characterListUpdated(m_characters);
    }


    m_chPlyMap.remove(m_chPlyMap.key(name));
    m_chPlyMap[ply] = name;

    emit entityRequireUpdate(name);
}

void ScriptEnvironnement::s_registerCharacter(QString ply)
{
    ScriptedEntity* ent = qobject_cast<ScriptedEntity*>(sender());
    if(ent == 0)
        return;

    QString name = m_entities.key(ent);
    if(name.isEmpty())
        return;

    addCharacter(name, ply);
}

QString ScriptEnvironnement::getPlayerCurrentCharacter(const QString& ply) const
{
    return m_chPlyMap.value(ply);
}

bool ScriptEnvironnement::playerHasCharacter(const QString& ply) const
{
    return m_chPlyMap.contains(ply);
}

QList<QPair<QString, int> > ScriptEnvironnement::getPlayerLanguages(const QString& ply)
{
    QList<QPair<QString, int> > ret;

    ScriptedEntity *ent = m_entities.value(m_chPlyMap.value(ply));

    if(ent == 0) //Obviously, there's no entity assigned to this player
        return ret; //Empty list

    return ent->getLanguages();
}
