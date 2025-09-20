#ifndef LUACOMP_H
#define LUACOMP_H

#include "lua.hpp"

#include <cstring>

/**
 * Opens individual libraries when one does not want them all
 */
static inline void luaJ_openlib_call(lua_State * L, const char * libName, lua_CFunction loader) {
    luaL_requiref(L, libName, loader, 1);
    lua_pop(L, 1);
}

static const luaL_Reg allAvailableLibs[] = {
    /* Standard Lua libraries */
    { "",          luaopen_base },
    { "_G",        luaopen_base },
    { LUA_LOADLIBNAME,   luaopen_package },
    { LUA_COLIBNAME,     luaopen_coroutine },
    { LUA_STRLIBNAME,    luaopen_string },
    { LUA_TABLIBNAME,    luaopen_table },
    { LUA_UTF8LIBNAME,   luaopen_utf8 },
    { LUA_MATHLIBNAME,   luaopen_math },
    { LUA_IOLIBNAME,     luaopen_io },
    { LUA_OSLIBNAME,     luaopen_os },
    { LUA_DBLIBNAME,     luaopen_debug },

    /* Pluto libraries */
    { PLUTO_CRYPTOLIBNAME,    luaopen_crypto },
    { PLUTO_JSONLIBNAME,      luaopen_json },
    { PLUTO_BASE32LIBNAME,    luaopen_base32 },
    { PLUTO_BASE64LIBNAME,    luaopen_base64 },
    { PLUTO_ASSERTLIBNAME,    luaopen_assert },
    { PLUTO_VECTOR3LIBNAME,   luaopen_vector3 },
    { PLUTO_URLLIBNAME,       luaopen_url },
    { PLUTO_STARLIBNAME,      luaopen_star },
    { PLUTO_CATLIBNAME,       luaopen_cat },
    { PLUTO_HTTPLIBNAME,      luaopen_http },
    { PLUTO_SCHEDULERLIBNAME, luaopen_scheduler },
    { PLUTO_BIGINTLIBNAME,    luaopen_bigint },
    { PLUTO_XMLLIBNAME,       luaopen_xml },
    { PLUTO_REGEXLIBNAME,     luaopen_regex },
    { PLUTO_FFILIBNAME,       luaopen_ffi },
    { PLUTO_CANVASLIBNAME,    luaopen_canvas },
    { PLUTO_BUFFERLIBNAME,    luaopen_buffer },

#ifndef __EMSCRIPTEN__
    { PLUTO_SOCKETLIBNAME,    luaopen_socket },
#endif

    /* Sentinel */
    { NULL, NULL }
};

static void luaJ_openlib(lua_State * L, const char * libName) {
    const luaL_Reg *lib = allAvailableLibs;
    for (; lib->func != NULL; lib++) {
        if (std::strcmp(lib->name, libName) == 0) {
            luaJ_openlib_call(L, lib->name, lib->func);
            return;
        }
    }
}

static int luaJ_compare(lua_State * L, int index1, int index2, int op) {
    if (op < 0) {
        return lua_compare(L, index1, index2, LUA_OPLT);
    } else if (op == 0) {
        return lua_compare(L, index1, index2, LUA_OPEQ);
    } else {
        return lua_compare(L, index1, index2, LUA_OPLE);
    }
}

static int luaJ_len(lua_State * L, int index) {
    return lua_rawlen(L, index);
}

static int luaJ_loadbuffer(lua_State * L, unsigned char * buffer, int size, const char * name) {
    return luaL_loadbuffer(L, (const char *) buffer, size, name);
}

static int luaJ_dobuffer(lua_State * L, unsigned char * buffer, int size, const char * name) {
    return (luaL_loadbuffer(L, (const char *) buffer, size, name) || lua_pcall(L, 0, LUA_MULTRET, 0));
}

static int luaJ_resume(lua_State * L, int narg) {
    int nresults;
    return lua_resume(L, NULL, narg, &nresults);
}

static int luaJ_initloader(lua_State * L) {
  return luaJ_insertloader(L, "searchers");
}

static int luaJ_dump (lua_State *L, lua_Writer writer, void * data) {
  return lua_dump (L, writer, data, true);
}

static int luaJ_isinteger(lua_State * L, int index) {
  return lua_isinteger(L, index);
}

#endif /* !LUACOMP_H */
