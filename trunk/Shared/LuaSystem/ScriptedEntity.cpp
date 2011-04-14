#include "ScriptedEntity.h"

#include <QTimer>
#include <QString>
#include <QStringList>

const char ScriptedEntity::className[] = "ScriptedEntity";

#define method(class, name) {#name, &class::name}

Lunar<ScriptedEntity>::RegType ScriptedEntity::methods[] = {
    method(ScriptedEntity, sendMessageToGM),
    method(ScriptedEntity, sendMessageToOwner),
    method(ScriptedEntity, sendMessageToAll),
    method(ScriptedEntity, sendMessageToPlayer),
    method(ScriptedEntity, syncData),
    method(ScriptedEntity, registerAsCharacter),
  /*method(ScriptedClass, sendMessage),*/
  {0,0}
};

ScriptedEntity::ScriptedEntity(const QString& file) : m_state()
{
    m_valid=false;

    Lunar<ScriptedEntity>::Register(m_state);

    m_fileName=file;

    m_valid=true;
    m_showUpdateError=true;
    m_needSync=true;

    if(luaL_dofile(m_state, file.toAscii())!=0)
    {
        LUA_ERROR(tr("Error loading script : %1").arg(file));
        m_valid=false;
    }


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

QStringList ScriptedEntity::getDataKeys()
{
    QStringList l;

    lua_settop(m_state,0);
    lua_getglobal(m_state,"data");
    if (!lua_istable(m_state,1))
    {
        lua_pop(m_state,1);
        return l;
    }

    lua_pushnil(m_state);  /* first key */
    while (lua_next(m_state, 1) != 0) //Iterate throught the table
    {
       /* uses 'key' (at index -2) and 'value' (at index -1) */
        if(lua_isstring(m_state, -2))
        {
            l << lua_tostring(m_state, -2);
        }

       lua_pop(m_state, 1); /* removes 'value'; keeps 'key' for next iteration */
    }

    lua_pop(m_state,1);

    return l;
}

QMap<QString, QString> ScriptedEntity::getDataPairs()
{
    QMap<QString, QString> ret;

    lua_settop(m_state,0);
    lua_getglobal(m_state,"data");
    if (!lua_istable(m_state,1))
    {
        lua_pop(m_state,1);
        return ret;
    }

    lua_pushnil(m_state);
    while (lua_next(m_state, 1) != 0)
    {
        if(lua_isstring(m_state, -2) && lua_isstring(m_state, -1))
            ret[lua_tostring(m_state, -2)] = lua_tostring(m_state, -1);
       lua_pop(m_state, 1);
    }
    lua_pop(m_state,1);

    return ret;
}


QMap<QString, EntityData> ScriptedEntity::getData()
{
    QMap<QString, QString> pairs=getDataPairs();
    QMap<QString, EntityData> ret;

    for(QMap<QString,QString>::const_iterator i=pairs.constBegin();i!=pairs.constEnd();++i)
    {
        bool b;
        EntityData s(getListStrOrNum(i.key(), &b));
        if(b)
        {
            s.shownName = i.value();
            ret[i.key()] = s;
        }
    }

    return ret;
}

QVariant ScriptedEntity::getListStrOrNum(const QString& name, bool* b)
{
    bool bp=false;
    if(b == NULL)
        b=&bp;

    *b=false;

    QVariant ret;
    lua_settop(m_state,0);
    lua_getglobal(m_state,name.toAscii());
    if (lua_isstring(m_state,1))
    {
        ret.setValue(QString(lua_tostring(m_state,1)));
        *b=true;
    }
    else if(lua_isnumber(m_state,1))
    {
        ret.setValue(lua_tonumber(m_state,1));
        *b=true;
    }
    else if(lua_istable(m_state, 1))
    {
        QStringList l;
        lua_pushnil(m_state);
        while (lua_next(m_state, 1) != 0)
        {
            if(lua_isstring(m_state, -1))
                l << lua_tostring(m_state, -1);
           lua_pop(m_state, 1);
        }
        if(!l.isEmpty())
        {
            ret.setValue(l);
            *b=true;
        }
    }
    lua_pop(m_state,1);
    return ret;
}

QString ScriptedEntity::getStr(const QString& name, bool* b)
{
    bool bp=false;
    if(b == NULL)
        b=&bp;

    *b=false;
    QString ret;
    lua_settop(m_state,0);
    lua_getglobal(m_state,name.toAscii());
    if (lua_isstring(m_state,1))
    {
        ret=lua_tostring(m_state,1);
        *b=true;
    }
    lua_pop(m_state,1);
    return ret;
}

double ScriptedEntity::getNumber(const QString& name, bool* b)
{
    bool bp=false;
    if(b == NULL)
        b=&bp;

    *b=false;
    double ret=0;
    lua_settop(m_state,0);
    lua_getglobal(m_state,name.toAscii());
    if (lua_isnumber(m_state,1))
    {
        ret=lua_tonumber(m_state,1);
        *b=true;
    }
    lua_pop(m_state,1);
    return ret;
}

bool ScriptedEntity::dataExist(const QString& name)
{
    lua_settop(m_state,0);
    lua_getglobal(m_state,name.toAscii());
    bool re = lua_isnoneornil(m_state, -1);
    lua_pop(m_state,1);
    return re;
}

QString ScriptedEntity::pushCode(const QString& code, bool* b)
{
    bool bp=false;
    if(b == NULL)
        b=&bp;

    if(!isValid())
    {
        *b=false;
        return tr("Script invalide");
    }
    int ret = luaL_dostring(m_state, code.toAscii());
    if(ret == 0)
    {
        *b=true;
        return QString();
    }
    *b=false;
    QString s = lua_tostring(m_state, -1) + '\n'; lua_pop(m_state, 1);
    return s;
}

