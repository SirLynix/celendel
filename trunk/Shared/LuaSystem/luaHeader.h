#ifndef LUA_H
#define LUA_H

extern "C"
{
    #include <lua/lualib.h>
    #include <lua/lauxlib.h>
}
#include <lua/lunar.h>

class Lua_State //RAII
{
    public:
    Lua_State() : state(lua_open()) { luaL_openlibs(state); }

    ~Lua_State() { lua_close(state); }

    inline operator lua_State*() {return state;} //Will act like a lua_State pointer

    private:

    lua_State *state;
};


#include <QDebug>
#ifdef __func__
    #define DEB() qDebug() << __FILE__ << " " << __func__ << " " << __LINE__ << "\t: "
#elif defined __FUNCTION__
    #define DEB() qDebug() << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << "\t: "
#else
    #define DEB() qDebug() << __FILE__ << " " << __LINE__ << "\t: "
#endif

#define LUA_ERROR() DEB()

#endif
