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

LUA_USERDATA(oslua_alphafx);
LUA_USERDATA(oslua_audiomeformat);
LUA_USERDATA(oslua_color);
LUA_USERDATA(oslua_dialogbutton);
LUA_USERDATA(oslua_dialogresult);
LUA_USERDATA(oslua_dialogstatus);
LUA_USERDATA(oslua_dialogtype);
LUA_USERDATA(oslua_fonttype);
LUA_USERDATA(oslua_intrafontoption);
LUA_USERDATA(oslua_key);
LUA_USERDATA(oslua_location);
LUA_USERDATA(oslua_mbaction);
LUA_USERDATA(oslua_pftype);
LUA_USERDATA(oslua_streamformat);

int oslua_register_font(lua_State *L);
int oslua_register_image(lua_State *L);
int oslua_register_sound(lua_State *L);

/* generic meta function for testing equality */
static int oslua_generic_meta_eq(lua_State *L) {
    lua_pushboolean(L, *(unsigned long int *)lua_touserdata(L, 1) == *(unsigned long int *)lua_touserdata(L, 2));
    return 1;
}

static int oslua_add_generic_meta(lua_State *L) {
    lua_pushcfunction(L, oslua_generic_meta_eq);
    lua_setfield(L, -2, "__eq");
    return 1;
}

/*** oalua_alphafx ***/
static int oslua_alphafx_meta_add(lua_State *L) {
    pushoslua_alphafx(L, checkoslua_alphafx(L, 1) | checkoslua_alphafx(L, 2));
    return 1;
}

static const luaL_reg oslua_alphafx_meta[] = {
    { "__add", oslua_alphafx_meta_add },
    { NULL, NULL }
};

/*** oslua_intrafontoption ***/
static int oslua_intrafontoption_meta_add(lua_State *L) {
    unsigned long int add;
    if(lua_isnumber(L, 2)) {
        add = luaL_checkint(L, 2);
        if(add >= 0 && add <= 255) {
            pushoslua_intrafontoption(L, checkoslua_intrafontoption(L, 1) + add);
        } else {
            luaL_error(L, "custom width must be from 0 to 255");
        }
    } else {
        pushoslua_intrafontoption(L, checkoslua_intrafontoption(L, 1) | checkoslua_intrafontoption(L, 2));
    }
    return 1;
}

static const luaL_reg oslua_intrafontoption_meta[] = {
    { "__add", oslua_intrafontoption_meta_add },
    { NULL, NULL }
};

/*** oslua_location ***/
static int oslua_location_meta_add(lua_State *L) {
    pushoslua_location(L, checkoslua_location(L, 1) + checkoslua_location(L, 2));
    return 1;
}

static const luaL_reg oslua_location_meta[] = {
    { "__add", oslua_location_meta_add },
    { NULL, NULL }
};

int oslua_register_types(lua_State *L) {

    registeroslua_alphafx(L);
    oslua_add_generic_meta(L);
    luaL_register(L, 0, oslua_alphafx_meta);

    registeroslua_audiomeformat(L);
    oslua_add_generic_meta(L);

    registeroslua_color(L);
    oslua_add_generic_meta(L);

    registeroslua_dialogbutton(L);
    oslua_add_generic_meta(L);

    registeroslua_dialogresult(L);
    oslua_add_generic_meta(L);

    registeroslua_dialogstatus(L);
    oslua_add_generic_meta(L);

    registeroslua_dialogtype(L);
    oslua_add_generic_meta(L);

    registeroslua_fonttype(L);
    oslua_add_generic_meta(L);

    registeroslua_intrafontoption(L);
    oslua_add_generic_meta(L);
    luaL_register(L, 0, oslua_intrafontoption_meta);

    registeroslua_key(L);
    oslua_add_generic_meta(L);

    registeroslua_location(L);
    oslua_add_generic_meta(L);
    luaL_register(L, 0, oslua_location_meta);

    registeroslua_mbaction(L);
    oslua_add_generic_meta(L);

    registeroslua_pftype(L);
    oslua_add_generic_meta(L);

    registeroslua_streamformat(L);
    oslua_add_generic_meta(L);

    /* not enums, but register all other types here */
    oslua_register_font(L);
    oslua_register_image(L);
    oslua_register_sound(L);

    return 1;
}
