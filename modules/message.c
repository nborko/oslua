/*
    Copyright (c)2009 by Nick Borko. All Rights Reserved.
    This file is part of OSLua.

    OSLua is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OSLua is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with OSLua.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "oslua.h"

static int oslua_message_Debug(lua_State *L) {
    char title[1000], where[1000];
    const char *msg = luaL_checkstring(L, 1);
    luaL_where(L, 1);
    strcpy(where, lua_tostring(L, -1));
    where[strlen(where) - 2] = '\0';
    sprintf(title, "Debug (%s)", where);
    oslMessageBox(msg, title, oslMake3Buttons(OSL_KEY_CROSS,OSL_MB_OK,OSL_KEY_TRIANGLE,OSL_MB_QUIT,0,0));
    return 1;
}

static int oslua_message_Make3Buttons(lua_State *L) {
    int b1, a1, b2 = 0, a2 = 0, b3 = 0, a3 = 0;
    int argc = lua_gettop(L);
    b1 = checkoslua_key(L, 1);
    a1 = checkoslua_mbaction(L, 2);
    if(argc > 2) {
        b2 = checkoslua_key(L, 3);
        a2 = checkoslua_mbaction(L, 4);
        if(argc > 4) {
            b3 = checkoslua_key(L, 5);
            a3 = checkoslua_mbaction(L, 6);
        }
    }
    lua_pushnumber(L, oslMake3Buttons(b1, a1, b2, a2, b3, a3));
    return 1;
}

static int oslua_message_Warning(lua_State *L) {
    oslWarning(luaL_checkstring(L, 1));
    return 1;
}

static int oslua_message_FatalError(lua_State *L) {
    oslFatalError(luaL_checkstring(L, 1));
    return 1;
}

static int oslua_message_Assert(lua_State *L) {
    char where[1000], msg[1000];
    if(lua_isboolean(L, 1)) {
        if(!lua_toboolean(L, 1)) {
            luaL_where(L, 1);
            strcpy(where, lua_tostring(L, -1));
            where[strlen(where) - 2] = '\0';
            sprintf(msg, "This program encountered a fatal error and must be terminated.\n\n%s", where);
            oslMessageBox(msg, "Fatal error", oslMake3Buttons(OSL_KEY_CROSS,OSL_MB_OK,OSL_KEY_TRIANGLE,OSL_MB_QUIT,0,0));
        }
    } else {
        luaL_error(L, "condition must evaluate to a boolean");
    }
    return 1;
}

static int oslua_message_MessageBox(lua_State *L) {
    oslMessageBox(luaL_checkstring(L, 1), luaL_checkstring(L, 2), luaL_checknumber(L, 3));
    return 1;
}

static const luaL_reg oslua_message_lib[] = {
    { "Debug", oslua_message_Debug },
    { "Make3Buttons", oslua_message_Make3Buttons },
    { "Warning", oslua_message_Warning },
    { "FatalError", oslua_message_FatalError },
    { "Assert", oslua_message_Assert },
    { "MessageBox", oslua_message_MessageBox },
    { NULL, NULL }
};

LUALIB_API int luaopen_oslua_message(lua_State *L) {
    luaL_register(L, "osl.message", oslua_message_lib);
    return 1;
}
