#include "ScriptedEntity.h"

#include <QTimer>
#include <QString>

const char ScriptedEntity::className[] = "ScriptedEntity";

#define method(class, name) {#name, &class::name}

Lunar<ScriptedEntity>::RegType ScriptedEntity::methods[] = {
    method(ScriptedEntity, sendMessageToGM),
  /*method(ScriptedClass, sendMessage),*/
  {0,0}
};

ScriptedEntity::ScriptedEntity(const QString& file) : m_state()
{
    m_valid=false;

    Lunar<ScriptedEntity>::Register(m_state);

    m_fileName=file;

    if(luaL_dofile(m_state, file.toAscii())!=0)
    {
        LUA_ERROR() << "Error loading script : " << file;
    }

    m_valid=true;

    m_elapsed.start();
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));
    m_updateTimer->setSingleShot(false);
    m_updateTimer->start(1000); //Update delay
    onInit();
}


ScriptedEntity::~ScriptedEntity()
{
    onDeath();
}

void ScriptedEntity::pause()
{
    m_updateTimer->stop();
}

void ScriptedEntity::unpause()
{
    m_updateTimer->start();
    m_elapsed.restart();
}

int ScriptedEntity::sendMessageToGM(lua_State* L)
{
    int argc = lua_gettop(L);
    if(argc != 1 || !lua_isstring(L,1))
    {
        LUA_ERROR() << "Error : invalid arguments";
        return 0;
    }

    QString msg(lua_tostring(L,1));

    emit sendGMMsg(msg);
    qDebug() << "GM msg : " << msg;

    return 0;
}

int ScriptedEntity::sendMessageToOwner(lua_State* L)
{
    int argc = lua_gettop(L);
    if(argc != 1 || !lua_isstring(L,1))
    {
        LUA_ERROR() << "Error : invalid arguments";
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
        LUA_ERROR() << "Error : invalid arguments";
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
        LUA_ERROR() << "Error : invalid arguments";
        return 0;
    }

    QString msg(lua_tostring(L,1));
    QString ply(lua_tostring(L,2));

    emit sendPlayerMsg(msg,ply);

    return 0;
}

void ScriptedEntity::onInit()
{
    callSimpleMethod("onInit");
}

void ScriptedEntity::onDeath()
{
    callSimpleMethod("onDeath");
}

void ScriptedEntity::callSimpleMethod(const QString& name)
{
    if(!isValid())
        return;

    lua_getglobal(m_state,name.toAscii());

    if (lua_isfunction(m_state,-1))
    {
        Lunar<ScriptedEntity>::push(m_state,this);

        if(lua_pcall(m_state,1,0,0))
        {
            LUA_ERROR() << "Error calling function " << name << " : " << lua_tostring(m_state,1);
            lua_pop(m_state,1);
        }
    }
    else
    {
        LUA_ERROR() << "Warning : no " << name << " callback function in LUA script";
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

        if(lua_pcall(m_state,4,0,0))
        {
            LUA_ERROR() << "Error calling function \"onDamage\" : " << lua_tostring(m_state,1);
            lua_pop(m_state,1);
            return 0;
        }

        return (int)lua_tonumber(m_state,-1);
    }
    else
    {
        LUA_ERROR() << "Error : no \"onDamage\" callback function";
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

        if(lua_pcall(m_state,2,0,0))
        {
            LUA_ERROR() << "Error calling function \"onUse\" : " << lua_tostring(m_state,1);
            lua_pop(m_state,1);
        }
    }
    else
    {
        LUA_ERROR() << "Error : no \"onUse\" callback function";
        lua_pop(m_state,1);
    }

}

void ScriptedEntity::onUpdate()
{
    int time = m_elapsed.elapsed();
    m_elapsed.restart();

    if(!isValid())
        return;

    lua_getglobal(m_state,"onUpdate");

    if (lua_isfunction(m_state,-1))
    {
        Lunar<ScriptedEntity>::push(m_state,this);
        lua_pushnumber(m_state,time);

        if(lua_pcall(m_state,2,0,0))
        {
            LUA_ERROR() << "Error calling function \"onUpdate\" : " << lua_tostring(m_state,1);
            lua_pop(m_state,1);
        }
    }
    else
    {
        LUA_ERROR() << "Error : no \"onUpdate\" callback function";
        lua_pop(m_state,1);
    }
}
