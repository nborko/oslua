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

int oslua_text_SetFont(lua_State *L);
int oslua_text_DeleteFont(lua_State *L);
int oslua_text_IntraFontSetStyle(lua_State *L);
int oslua_text_IntraFontPrintColumn(lua_State *L);

LUA_USERDATA(oslua_font)

LUA_GETTER(oslua_font, charWidth, lua_pushinteger);
LUA_GETTER(oslua_font, charHeight, lua_pushinteger);
LUA_GETTER(oslua_font, fontType, pushoslua_fonttype);

static lua_userdata_member_mapping oslua_font_getters[] = {
    LUA_GETTER_MAP(oslua_font, charWidth),
    LUA_GETTER_MAP(oslua_font, charHeight),
    LUA_GETTER_MAP(oslua_font, fontType),
    { NULL, NULL }
};

LUA_GETTER_META_INDEX(oslua_font, oslua_font_getters);

static const luaL_reg oslua_font_methods[] = {
    { "SetFont", oslua_text_SetFont },
    { "SetStyle", oslua_text_IntraFontSetStyle },
    { "PrintColumn", oslua_text_IntraFontPrintColumn },
    { NULL, NULL }
};

static const luaL_reg oslua_font_meta[] = {
    { "__gc", oslua_text_DeleteFont },
    { NULL, NULL }
};

int oslua_register_font(lua_State *L) {

    luaL_register(L, "oslua_font", oslua_font_methods);
    int methods = lua_gettop(L);

    registeroslua_font(L);
    luaL_register(L, 0, oslua_font_meta);
    LUA_REGISTER_GETTERS(oslua_font, methods);

    return 1;
}
