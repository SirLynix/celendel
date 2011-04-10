#include "ScriptSandbox.h"

ScriptSandbox::ScriptSandbox() : m_state()
{
    m_error = false;
}

bool ScriptSandbox::pushCode(const QString& code)
{
    int ret = luaL_dostring(m_state, code.toAscii());

    if(ret==0)
        return false;

    m_error = true;

    m_errorTxt += lua_tostring(m_state, -1) + '\n';
    lua_pop(m_state, 1);

    return true;
}
