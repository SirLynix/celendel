#include "ScriptedEntity.h"

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //                                                            C++->Lua                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ScriptedEntity::onInit()
{
    callSimpleMethod("onInit");
}

void ScriptedEntity::onDeath()
{
    callSimpleMethod("onDeath");
}

void ScriptedEntity::once()
{
    callSimpleMethod("once");
    m_tempusFugit.restart();
    luaL_dostring(m_state, "function once(this) end");
}

void ScriptedEntity::callSimpleMethod(const QString& name)
{
    if(!isValid())
        return;

    lua_getglobal(m_state,name.toAscii());

    if (lua_isfunction(m_state,-1))
    {
        Lunar<ScriptedEntity>::push(m_state,this);

        m_tempusFugit.restart();
        if(lua_pcall(m_state,1,0,0))
        {
            LUA_ERROR("Error calling function " + name + " : " + lua_tostring(m_state,1));
            lua_pop(m_state,1);
        }
    }
    else
    {
        LUA_ERROR("Warning : no " + name + " callback function in LUA script");
        lua_pop(m_state,1);
    }
}

int ScriptedEntity::onDamage(int amount, const QString& type, const QString& from)
{
    if(!isValid())
        return 0;

    lua_getglobal(m_state,"onDamage");

    if (lua_isfunction(m_state,-1))
    {
        Lunar<ScriptedEntity>::push(m_state,this);
        lua_pushnumber(m_state,amount);
        lua_pushstring(m_state,type.toAscii());
        lua_pushstring(m_state,from.toAscii());

        m_tempusFugit.restart();
        if(lua_pcall(m_state,4,0,0))
        {
            LUA_ERROR(tr("Error calling function \"onDamage\" : %1").arg(lua_tostring(m_state,1)));
            lua_pop(m_state,1);
            return 0;
        }

        return (int)lua_tonumber(m_state,-1);
    }
    else
    {
        LUA_ERROR(tr("Error : no \"onDamage\" callback function"));
        lua_pop(m_state,1);
    }

    return 0;
}

void ScriptedEntity::onUse(const QString& user)
{
    if(!isValid())
        return;

    lua_getglobal(m_state,"onUse");

    if (lua_isfunction(m_state,-1))
    {
        Lunar<ScriptedEntity>::push(m_state,this);
        lua_pushstring(m_state,user.toAscii());

        m_tempusFugit.restart();
        if(lua_pcall(m_state,2,0,0))
        {
            LUA_ERROR(tr("Error calling function \"onUse\" : %1").arg(lua_tostring(m_state,1)));
            lua_pop(m_state,1);
        }
    }
    else
    {
        LUA_ERROR(tr("Error : no \"onUse\" callback function"));
        lua_pop(m_state,1);
    }

}

void ScriptedEntity::onUpdate()
{
    int time = m_elapsed.elapsed();
    m_elapsed.restart();

    if(!isValid())
        return;

    if(m_needSync)
    {
        emit dataChanged();
        m_needSync=false;
    }

    once();

    lua_getglobal(m_state,"onUpdate");
    if (lua_isfunction(m_state,-1))
    {
        Lunar<ScriptedEntity>::push(m_state,this);
        lua_pushnumber(m_state,time);

        m_tempusFugit.restart();
        if(lua_pcall(m_state,2,0,0))
        {
            LUA_ERROR(tr("Error calling function \"onUpdate\" : %1").arg(lua_tostring(m_state,1)));
            lua_pop(m_state,1);
        }
    }
    else
    {
        if(m_showUpdateError)
        {
            m_showUpdateError=false;
            LUA_ERROR(tr("Error : no \"onUpdate\" callback function"));
        }

        lua_pop(m_state,1);
    }
}
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //                                                            Lua->C++                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScriptedEntity::sendMessageToGM(lua_State* L)
{
    int argc = lua_gettop(L);
    if(argc != 1 || !lua_isstring(L,1))
    {
        LUA_ERROR(tr("Error : invalid arguments"));
        return 0;
    }

    QString msg(lua_tostring(L,1));

    emit sendGMMsg(msg);

    return 0;
}

int ScriptedEntity::sendMessageToOwner(lua_State* L)
{
    int argc = lua_gettop(L);
    if(argc != 1 || !lua_isstring(L,1))
    {
        LUA_ERROR(tr("Error : invalid arguments"));
        return 0;
    }

    QString msg(lua_tostring(L,1));
    emit sendOwnerMsg(msg);
    return 0;
}

int ScriptedEntity::sendMessageToAll(lua_State* L)
{
    int argc = lua_gettop(L);
    if(argc != 1 || !lua_isstring(L,1))
    {
        LUA_ERROR(tr("Error : invalid arguments"));
        return 0;
    }

    QString msg(lua_tostring(L,1));
    emit sendMsg(msg);
    return 0;
}

int ScriptedEntity::sendMessageToPlayer(lua_State* L)
{
    int argc = lua_gettop(L);
    if(argc != 2 || !lua_isstring(L,1) || !lua_isstring(L,1))
    {
        LUA_ERROR(tr("Error : invalid arguments"));
        return 0;
    }

    QString msg(lua_tostring(L,1));
    QString ply(lua_tostring(L,2));
    emit sendPlayerMsg(msg,ply);
    return 0;
}

int ScriptedEntity::syncData(lua_State* L)
{
    int argc = lua_gettop(L);
    if(argc > 0)
    {
        LUA_ERROR(tr("Error : too much arguments"));
        return 0;
    }

    m_needSync=true;
    return 0;
}

int ScriptedEntity::registerAsCharacter(lua_State* L)
{
    int argc = lua_gettop(L);
    if(argc > 0)
    {
        LUA_ERROR(tr("Error : too much arguments"));
        return 0;
    }

    emit registerCharacter();
    return 0;
}

