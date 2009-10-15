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

#include <stdlib.h>
#include <string.h>

#include "userdata.h"

int lua_userdata_getter(lua_State *L, void *d, lua_userdata_member_mapping mapping[]) {
    /* assumes type checking of d has been done */
    const char *field = luaL_checkstring(L, 2);
    int i;
    for(i = 0; mapping[i].field; i++) {
        if(!strcmp(field, mapping[i].field)) {
            mapping[i].gsetter(L, d);
            return 1;
        }
    }
    if(lua_getmetatable(L, 1)) {
        if(luaL_getmetafield(L, 1, "__metatable")) {
            lua_getfield(L, -1, field);
            lua_remove(L, -2);
        } else {
            lua_pushnil(L);
        }
        lua_remove(L, -2);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

int lua_userdata_register_getters(lua_State *L, int methods_index, lua_CFunction getter_meta_index) {
    lua_pushcfunction(L, getter_meta_index);
    lua_setfield(L, -2, "__index");
    if(methods_index) {
        lua_pushvalue(L, methods_index);
        lua_setfield(L, -2, "__metatable");
    }
    return 1;
}

int lua_userdata_setter(lua_State *L, void *d, lua_userdata_member_mapping mapping[]) {
    /* assumes type checking of d has been done */
    const char *field = luaL_checkstring(L, 2);
    int i;
    for(i = 0; mapping[i].field; i++) {
        if(!strcmp(field, mapping[i].field)) {
            mapping[i].gsetter(L, d);
            return 1;
        }
    }
    luaL_error(L, "cannot set value on userdata");
    return 1;
}

int lua_userdata_register_setters(lua_State *L, lua_CFunction setter_meta_newindex) {
    lua_pushcfunction(L, setter_meta_newindex);
    lua_setfield(L, -2, "__newindex");
    return 1;
}
