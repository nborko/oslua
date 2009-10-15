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

int oslua_text_SetFont(lua_State *L) {
    oslSetFont(checkoslua_font(L, 1));
    return 1;
}

static int oslua_text_InitConsole(lua_State *L) {
    oslInitConsole();
    return 1;
}

static int oslua_text_LoadFontFile(lua_State *L) {
    OSL_FONT *f = oslLoadFontFile(luaL_checkstring(L, 1));
    if(f) {
        pushoslua_font(L, f);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static int oslua_text_DrawChar(lua_State *L) {
    oslDrawChar(luaL_checkint(L, 1), luaL_checkint(L, 2), *luaL_checkstring(L, 3));
    return 1;
}

static int oslua_text_DrawString(lua_State *L) {
    oslDrawString(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkstring(L, 3));
    return 1;
}

static int oslua_text_DrawStringLimited(lua_State *L) {
    int width = luaL_checkint(L, 3);
    if(width > 0) {
        oslDrawStringLimited(luaL_checkint(L, 1), luaL_checkint(L, 2), width, luaL_checkstring(L, 4));
    } else {
        luaL_error(L, "width must be greater than 0");
    }
    return 1;
}

static int oslua_text_ConsolePrint(lua_State *L) {
    oslConsolePrint(luaL_checkstring(L, 1));
    return 1;
}

static int oslua_text_SetTextColor(lua_State *L) {
    oslSetTextColor(checkoslua_color(L, 1));
    return 1;
}

static int oslua_text_SetBkColor(lua_State *L) {
    oslSetBkColor(checkoslua_color(L, 1));
    return 1;
}

static int oslua_text_DrawTextBox(lua_State *L) {
    oslDrawTextBox(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4), luaL_checkstring(L, 5), 0);
    return 1;
}

int oslua_text_DeleteFont(lua_State *L) {
    OSL_FONT *font = checkoslua_font(L, 1);
    oslDeleteFont(font);
    if(font == osl_curFont) {
        oslSetFont(osl_sceFont); // just in case we deleted the current font
    }
    return 1;
}

static int oslua_text_GetStringWidth(lua_State *L) {
    lua_pushinteger(L, oslGetStringWidth(luaL_checkstring(L, 1)));
    return 1;
}

static int oslua_text_GetTextBoxHeight(lua_State *L) {
    lua_pushinteger(L, oslGetTextBoxHeight(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkstring(L, 3), 0));
    return 1;
}

/*
static int oslua_text_IntraFontInit(lua_State *L) {
    lua_pushinteger(L, oslIntraFontInit(checkoslua_intrafontoption(L, 1)));
    return 1;
}
*/

static int oslua_text_LoadIntraFontFile(lua_State *L) {
    OSL_FONT *f = oslLoadIntraFontFile(luaL_checkstring(L, 1), checkoslua_intrafontoption(L, 2));
    if(f) {
        pushoslua_font(L, f);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

int oslua_text_IntraFontSetStyle(lua_State *L) {
    oslIntraFontSetStyle(checkoslua_font(L, 1), luaL_checknumber(L, 2), checkoslua_color(L, 3), checkoslua_color(L, 4), checkoslua_intrafontoption(L, 5));
    return 1;
}

int oslua_text_IntraFontPrintColumn(lua_State *L) {
    if(lua_isboolean(L, 5)) {
        lua_pushnumber(L, oslIntraFontPrintColumn(checkoslua_font(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), lua_toboolean(L, 5), luaL_checkstring(L, 6)));
    } else {
        luaL_typerror(L, 5, "boolean");
        lua_error(L);
    }
    return 1;
}

/*
static int oslua_text_IntraFontShutdown(lua_State *L) {
    oslIntraFontShutdown();
    return 1;
}
*/

static int oslua_text_Printf(lua_State *L) {
    oslPrintf(luaL_checkstring(L, 1));
    return 1;
}

static int oslua_text_Printf_xy(lua_State *L) {
    oslPrintf_xy(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkstring(L, 3));
    return 1;
}

static int oslua_text_Cls(lua_State *L) {
    oslCls();
    return 1;
}

static int oslua_text_MoveTo(lua_State *L) {
    oslMoveTo(luaL_checkint(L, 1), luaL_checkint(L, 2));
    return 1;
}

static const luaL_reg oslua_text_lib[] = {
    { "SetFont", oslua_text_SetFont },
    { "InitConsole", oslua_text_InitConsole },
    { "LoadFontFile", oslua_text_LoadFontFile },
    { "DrawChar", oslua_text_DrawChar },
    { "DrawString", oslua_text_DrawString },
    { "DrawStringLimited", oslua_text_DrawStringLimited },
    { "ConsolePrint", oslua_text_ConsolePrint },
    { "SetTextColor", oslua_text_SetTextColor },
    { "SetBkColor", oslua_text_SetBkColor },
    { "DrawTextBox", oslua_text_DrawTextBox },
    // handled by __gc{ "DeleteFont", oslua_text_DeleteFont },
    { "GetStringWidth", oslua_text_GetStringWidth },
    { "GetTextBoxHeight", oslua_text_GetTextBoxHeight },
    // handle globally { "IntraFontInit", oslua_text_IntraFontInit },
    { "LoadIntraFontFile", oslua_text_LoadIntraFontFile },
    { "IntraFontSetStyle", oslua_text_IntraFontSetStyle },
    { "IntraFontPrintColumn", oslua_text_IntraFontPrintColumn },
    // handle globally { "IntraFontShutdown", oslua_text_IntraFontShutdown },
    { "Printf", oslua_text_Printf },
    { "Printf_xy", oslua_text_Printf_xy },
    { "Cls", oslua_text_Cls },
    { "MoveTo", oslua_text_MoveTo },
    { NULL, NULL }
};

LUALIB_API int luaopen_oslua_text(lua_State *L) {
    luaL_register(L, "osl.text", oslua_text_lib);
    return 1;
}
