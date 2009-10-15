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

static int oslua_network_NetInit(lua_State *L) {
    oslNetInit();
    return 1;
}

static int oslua_network_NetTerm(lua_State *L) {
    oslNetTerm();
    return 1;
}

static const luaL_reg oslua_network_lib[] = {
    { "NetInit", oslua_network_NetInit },
    { "NetTerm", oslua_network_NetTerm },
    { NULL, NULL }
};

LUALIB_API int luaopen_oslua_network(lua_State *L) {
    luaL_register(L, "osl.network", oslua_network_lib);
    return 1;
}
