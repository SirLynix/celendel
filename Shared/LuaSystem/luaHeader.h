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
    Lua_State() : state(lua_open())
    {
        //luaL_openlibs(state); //Will also load the files i/o...

        lua_pushcfunction(state, luaopen_table); //Tables
        lua_pushliteral(state, LUA_TABLIBNAME);
        lua_call(state, 1, 0);

        lua_pushcfunction(state, luaopen_string); //Strings
        lua_pushliteral(state, LUA_STRLIBNAME);
        lua_call(state, 1, 0);

        lua_pushcfunction(state, luaopen_math); //Math
        lua_pushliteral(state, LUA_MATHLIBNAME);
        lua_call(state, 1, 0);

    }

    ~Lua_State() { lua_close(state); }

    inline operator lua_State*() {return state;} //Will act like a lua_State pointer

    private:

    lua_State *state;
};


#endif
