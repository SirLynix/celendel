#include "ScriptEnvironnement.h"

#include "..\Shared\LuaSystem\ScriptedEntity.h"

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

QList<EntityInformations> ScriptEnvironnement::getEntitiesInformations()
{
    QList<EntityInformations> list;

    for(QMap<QString, ScriptedEntity*>::const_iterator i = m_entities.constBegin(); i!=m_entities.constEnd();++i)
    {
        list.append(EntityInformations());
        EntityInformations& ei = list.last();
        ei.name = i.key();
        ei.data = i.value()->getData();
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
