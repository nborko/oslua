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

int oslua_images_DeleteImage(lua_State *L) {
    oslDeleteImage(checkoslua_image(L, 1));
    return 1;
}
    
int oslua_images_LoadImageFile(lua_State *L) {
    OSL_IMAGE *i = oslLoadImageFile((char *)luaL_checkstring(L, 1), checkoslua_location(L, 2), checkoslua_pftype(L, 3));
    if(i) {
        pushoslua_image(L, i);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

int oslua_images_LoadImageFilePNG(lua_State *L) {
    OSL_IMAGE *i = oslLoadImageFilePNG((char *)luaL_checkstring(L, 1), checkoslua_location(L, 2), checkoslua_pftype(L, 3));
    if(i) {
        pushoslua_image(L, i);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

int oslua_images_LoadImageFileJPG(lua_State *L) {
    OSL_IMAGE *i = oslLoadImageFileJPG((char *)luaL_checkstring(L, 1), checkoslua_location(L, 2), checkoslua_pftype(L, 3));
    if(i) {
        pushoslua_image(L, i);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

int oslua_images_LoadImageFileGIF(lua_State *L) {
    OSL_IMAGE *i = oslLoadImageFileGIF((char *)luaL_checkstring(L, 1), checkoslua_location(L, 2), checkoslua_pftype(L, 3));
    if(i) {
        pushoslua_image(L, i);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

int oslua_images_DrawImageXY(lua_State *L) {
    oslDrawImageXY(checkoslua_image(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3));
    return 1;
}
    
int oslua_images_DrawImage(lua_State *L) {
    oslDrawImage(checkoslua_image(L, 1));
    return 1;
}

int oslua_images_SetImageFrameSize(lua_State *L) {
    oslSetImageFrameSize(checkoslua_image(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3));
    return 1;
}

int oslua_images_SetImageFrame(lua_State *L) {
    oslSetImageFrame(checkoslua_image(L, 1), luaL_checkint(L, 2));
    return 1;
}

const luaL_reg oslua_images_lib[] = {
    // handled by __gc { "DeleteImage", oslua_images_DeleteImage },
    { "LoadImageFile", oslua_images_LoadImageFile },
    { "LoadImageFilePNG", oslua_images_LoadImageFilePNG },
    { "LoadImageFileJPG", oslua_images_LoadImageFileJPG },
    { "LoadImageFileGIF", oslua_images_LoadImageFileGIF },
    { "DrawImageXY", oslua_images_DrawImageXY },
    { "DrawImage", oslua_images_DrawImage },
    { "SetImageFrameSize", oslua_images_SetImageFrameSize },
    { "SetImageFrame", oslua_images_SetImageFrame },
    { NULL, NULL }
};

LUALIB_API int luaopen_oslua_images(lua_State *L) {
    luaL_register(L, "osl.image", oslua_images_lib);
    return 1;
}
