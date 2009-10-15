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

int oslua_images_DeleteImage(lua_State *L);
int oslua_images_DrawImageXY(lua_State *L);
int oslua_images_DrawImage(lua_State *L);
int oslua_images_SetImageFrameSize(lua_State *L);
int oslua_images_SetImageFrame(lua_State *L);

LUA_USERDATA(oslua_image)

LUA_GETTER(oslua_image, sizeX, lua_pushinteger)
LUA_GETTER(oslua_image, sizeY, lua_pushinteger)
LUA_GETTER(oslua_image, sysSizeX, lua_pushinteger)
LUA_GETTER(oslua_image, sysSizeY, lua_pushinteger)
LUA_GETTER(oslua_image, realSizeX, lua_pushinteger)
LUA_GETTER(oslua_image, realSizeY, lua_pushinteger)
LUA_GETTER(oslua_image, flags, lua_pushinteger) // NOTE: change to oslua_type
LUA_GETTER(oslua_image, totalSize, lua_pushinteger)
LUA_GETTER(oslua_image, location, pushoslua_location)
LUA_GETTER(oslua_image, pixelFormat, pushoslua_pftype)
LUA_GETTER(oslua_image, frameSizeX, lua_pushinteger)
LUA_GETTER(oslua_image, frameSizeY, lua_pushinteger)
LUA_GETTER(oslua_image, x, lua_pushinteger)
LUA_SETTER(oslua_image, x, luaL_checkint)
LUA_GETTER(oslua_image, y, lua_pushinteger)
LUA_SETTER(oslua_image, y, luaL_checkint)
LUA_GETTER(oslua_image, stretchX, lua_pushinteger)
LUA_GETTER(oslua_image, stretchY, lua_pushinteger)
LUA_GETTER(oslua_image, offsetX0, lua_pushnumber)
LUA_GETTER(oslua_image, offsetY0, lua_pushnumber)
LUA_GETTER(oslua_image, offsetX1, lua_pushnumber)
LUA_GETTER(oslua_image, offsetY1, lua_pushnumber)
LUA_GETTER(oslua_image, centerX, lua_pushinteger)
LUA_GETTER(oslua_image, centerY, lua_pushinteger)
LUA_GETTER(oslua_image, angle, lua_pushinteger)
LUA_SETTER(oslua_image, angle, luaL_checkint)

static lua_userdata_member_mapping oslua_image_getters[] = {
    LUA_GETTER_MAP(oslua_image, sizeX),
    LUA_GETTER_MAP(oslua_image, sizeY),
    LUA_GETTER_MAP(oslua_image, sysSizeX),
    LUA_GETTER_MAP(oslua_image, sysSizeY),
    LUA_GETTER_MAP(oslua_image, realSizeX),
    LUA_GETTER_MAP(oslua_image, realSizeY),
    LUA_GETTER_MAP(oslua_image, flags),
    LUA_GETTER_MAP(oslua_image, totalSize),
    LUA_GETTER_MAP(oslua_image, location),
    LUA_GETTER_MAP(oslua_image, pixelFormat),
    LUA_GETTER_MAP(oslua_image, frameSizeX),
    LUA_GETTER_MAP(oslua_image, frameSizeY),
    LUA_GETTER_MAP(oslua_image, x),
    LUA_GETTER_MAP(oslua_image, y),
    LUA_GETTER_MAP(oslua_image, stretchX),
    LUA_GETTER_MAP(oslua_image, stretchY),
    LUA_GETTER_MAP(oslua_image, offsetX0),
    LUA_GETTER_MAP(oslua_image, offsetY0),
    LUA_GETTER_MAP(oslua_image, offsetX1),
    LUA_GETTER_MAP(oslua_image, offsetY1),
    LUA_GETTER_MAP(oslua_image, centerX),
    LUA_GETTER_MAP(oslua_image, centerY),
    LUA_GETTER_MAP(oslua_image, angle),
    { NULL, NULL }
};

static lua_userdata_member_mapping oslua_image_setters[] = {
    LUA_SETTER_MAP(oslua_image, x),
    LUA_SETTER_MAP(oslua_image, y),
    LUA_SETTER_MAP(oslua_image, angle),
    { NULL, NULL }
};

LUA_GETTER_META_INDEX(oslua_image, oslua_image_getters)
LUA_SETTER_META_NEWINDEX(oslua_image, oslua_image_setters)

static const luaL_reg oslua_image_methods[] = {
    { "DrawImageXY", oslua_images_DrawImageXY },
    { "DrawImage", oslua_images_DrawImage },
    { "SetImageFrameSize", oslua_images_SetImageFrameSize },
    { "SetImageFrame", oslua_images_SetImageFrame },
    { NULL, NULL }
};

static const luaL_reg oslua_image_meta[] = {
    { "__gc", oslua_images_DeleteImage },
    { NULL, NULL }
};

int oslua_register_image(lua_State *L) {

    luaL_register(L, "oslua_image", oslua_image_methods);
    int methods = lua_gettop(L);

    registeroslua_image(L);
    luaL_register(L, 0, oslua_image_meta);
    LUA_REGISTER_GETTERS(oslua_image, methods);
    LUA_REGISTER_SETTERS(oslua_image);

    return 1;
}
