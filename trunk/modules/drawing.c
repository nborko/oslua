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

/*
static int oslua_drawing_InitGfx(lua_State *L) {
    //int pixelFormat = checkoslua_pftype(L, 1);
    if(lua_isboolean(L, 2)) {
        //oslInitGfx(pixelFormat, lua_toboolean(L, 2));
    } else {
        luaL_error(L, "bDoubleBuffer must be true or false");
    }
    return 1;
}
*/
static int oslua_drawing_StartDrawing(lua_State *L) {
    oslStartDrawing();
    return 1;
}

static int oslua_drawing_EndDrawing(lua_State *L) {
    oslEndDrawing();
    return 1;
}

static int oslua_drawing_SyncDrawing(lua_State *L) {
    oslSyncDrawing();
    return 1;
}

static int oslua_drawing_SwapBuffers(lua_State *L) {
    oslSwapBuffers();
    return 1;
}

/*
static int oslua_drawing_EndGfx(lua_State *L) {
    oslEndGfx();
    return 1;
}

static int oslua_drawing_SetSysDisplayListSize(lua_State *L) {
    oslSetSysDisplayListSize(luaL_checkint(L, 1));
    return 1;
}
*/

static int oslua_drawing_ResetScreenClipping(lua_State *L) {
    oslResetScreenClipping();
    return 1;
}

static int oslua_drawing_ClearScreen(lua_State *L) {
    oslClearScreen(checkoslua_color(L, 1));
    return 1;
}

static int oslua_drawing_SetScreenClipping(lua_State *L) {
    oslSetScreenClipping(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4));
    return 1;
}

static int oslua_drawing_SetDepthTest(lua_State *L) {
    if(lua_isboolean(L, 1)) {
        oslSetDepthTest(lua_toboolean(L, 1));
    } else {
        luaL_typerror(L, 1, "boolean");
        lua_error(L);
    }
    return 1;
}

static int oslua_drawing_SetAlpha(lua_State *L) {
    int argc = lua_gettop(L);
    unsigned long int effect, coeff1, coeff2;
    effect = checkoslua_alphafx(L, 1);
    if(argc < 2) {
        coeff1 = 0;
    } else if(lua_isnumber(L, 2)) {
        coeff1 = luaL_checkint(L, 2);
        if(coeff1 < 0 || coeff1 > 255) {
            luaL_error(L, "alpha coeffecient must be from 0 to 255");
            return 1;
        }
    } else {
        coeff1 = checkoslua_color(L, 2);
    }
    if(argc < 3) {
        oslSetAlpha(effect, coeff1);
    } else {
        if(lua_isnumber(L, 3)) {
            coeff2 = luaL_checkint(L, 3);
            if(coeff2 < 0 || coeff2 > 255) {
                luaL_error(L, "alpha coeffecient must be from 0 to 255");
                return 1;
            } 
        } else {
            coeff2 = checkoslua_color(L, 2);
        }
        oslSetAlpha2(effect, coeff1, coeff1);
    }
    return 1;
}

static int oslua_drawing_GetAlpha(lua_State *L) {
    OSL_ALPHA_PARAMS params;
    oslGetAlphaEx(&params);
    pushoslua_alphafx(L, params.effect);
    if(params.coeff1 < 256) {
        lua_pushinteger(L, params.coeff1);
    } else {
        pushoslua_color(L, params.coeff1);
    }
    if(params.coeff2 < 256) {
        lua_pushinteger(L, params.coeff2);
    } else {
        pushoslua_color(L, params.coeff2);
    }
    return 1;
}

static int oslua_drawing_SetBilinearFilter(lua_State *L) {
    if(lua_isboolean(L, 1)) {
        oslSetBilinearFilter(lua_toboolean(L, 1));
    } else {
        luaL_typerror(L, 1, "boolean");
        lua_error(L);
    }
    return 1;
}

static int oslua_drawing_SetDithering(lua_State *L) {
    if(lua_isboolean(L, 1)) {
        oslSetDithering(lua_toboolean(L, 1));
    } else {
        luaL_typerror(L, 1, "boolean");
        lua_error(L);
    }
    return 1;
}

static int oslua_drawing_SetTransparentColor(lua_State *L) {
    oslSetTransparentColor(checkoslua_color(L, 1));
    return 1;
}

static int oslua_drawing_DisableTransparentColor(lua_State *L) {
    oslDisableTransparentColor();
    return 1;
}

static int oslua_drawing_RGB(lua_State *L) {
    pushoslua_color(L, RGB(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3)));
    return 1;
}

static int oslua_drawing_RGBA(lua_State *L) {
    pushoslua_color(L, RGBA(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4)));
    return 1;
}

static int oslua_drawing_RGB12(lua_State *L) {
    pushoslua_color(L, RGB12(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3)));
    return 1;
}

static int oslua_drawing_RGBA12(lua_State *L) {
    pushoslua_color(L, RGBA12(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4)));
    return 1;
}

static int oslua_drawing_RGB15(lua_State *L) {
    pushoslua_color(L, RGB15(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3)));
    return 1;
}

static int oslua_drawing_RGBA15(lua_State *L) {
    pushoslua_color(L, RGBA15(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L, 3), luaL_checkint(L, 4)));
    return 1;
}

static int oslua_drawing_RgbaGet8888(lua_State *L) {
    int red, green, blue, alpha;
    oslRgbaGet8888(checkoslua_color(L, 1), red, green, blue, alpha);
    lua_pushinteger(L, red);
    lua_pushinteger(L, green);
    lua_pushinteger(L, blue);
    lua_pushinteger(L, alpha);
    return 1;
}

static int oslua_drawing_RgbaGet4444(lua_State *L) {
    int red, green, blue, alpha;
    oslRgbaGet4444(checkoslua_color(L, 1), red, green, blue, alpha);
    lua_pushinteger(L, red);
    lua_pushinteger(L, green);
    lua_pushinteger(L, blue);
    lua_pushinteger(L, alpha);
    return 1;
}

static int oslua_drawing_RgbaGet5551(lua_State *L) {
    int red, green, blue, alpha;
    oslRgbaGet5551(checkoslua_color(L, 1), red, green, blue, alpha);
    lua_pushinteger(L, red);
    lua_pushinteger(L, green);
    lua_pushinteger(L, blue);
    lua_pushinteger(L, alpha);
    return 1;
}

static int oslua_drawing_RgbGet5650(lua_State *L) {
    int red, green, blue;
    oslRgbGet5650(checkoslua_color(L, 1), red, green, blue);
    lua_pushinteger(L, red);
    lua_pushinteger(L, green);
    lua_pushinteger(L, blue);
    return 1;
}

static int oslua_drawing_DrawLine(lua_State *L) {
    oslDrawLine(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L,3), luaL_checkint(L, 4), checkoslua_color(L, 5));
    return 1;
}

static int oslua_drawing_DrawRect(lua_State *L) {
    oslDrawRect(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L,3), luaL_checkint(L, 4), checkoslua_color(L, 5));
    return 1;
}

static int oslua_drawing_DrawFillRect(lua_State *L) {
    oslDrawFillRect(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L,3), luaL_checkint(L, 4), checkoslua_color(L, 5));
    return 1;
}

static int oslua_drawing_DrawGradientRect(lua_State *L) {
    oslDrawGradientRect(luaL_checkint(L, 1), luaL_checkint(L, 2), luaL_checkint(L,3), luaL_checkint(L, 4), checkoslua_color(L, 5), checkoslua_color(L, 6), checkoslua_color(L, 7), checkoslua_color(L, 8));
    return 1;
}

static const luaL_reg oslua_drawing_lib[] = {
    // handled globally { "InitGfx", oslua_drawing_InitGfx },
    { "StartDrawing", oslua_drawing_StartDrawing },
    { "EndDrawing", oslua_drawing_EndDrawing },
    { "SyncDrawing", oslua_drawing_SyncDrawing },
    { "SwapBuffers", oslua_drawing_SwapBuffers },
    // handled globally { "EndGfx", oslua_drawing_EndGfx },
    // don't allow { "SetSysDisplayListSize", oslua_drawing_SetSysDisplayListSize },
    { "ResetScreenClipping", oslua_drawing_ResetScreenClipping },
    { "ClearScreen", oslua_drawing_ClearScreen },
    { "SetScreenClipping", oslua_drawing_SetScreenClipping },
    { "SetDepthTest", oslua_drawing_SetDepthTest },
    { "SetAlpha", oslua_drawing_SetAlpha },
    { "GetAlpha", oslua_drawing_GetAlpha },
    { "SetBilinearFilter", oslua_drawing_SetBilinearFilter },
    { "SetDithering", oslua_drawing_SetDithering },
    { "SetTransparentColor", oslua_drawing_SetTransparentColor },
    { "DisableTransparentColor", oslua_drawing_DisableTransparentColor },
    { "RGB", oslua_drawing_RGB },
    { "RGBA", oslua_drawing_RGBA },
    { "RGB12", oslua_drawing_RGB12 },
    { "RGBA12", oslua_drawing_RGBA12 },
    { "RGB15", oslua_drawing_RGB15 },
    { "RGBA15", oslua_drawing_RGBA15 },
    { "RgbaGet8888", oslua_drawing_RgbaGet8888 },
    { "RgbaGet4444", oslua_drawing_RgbaGet4444 },
    { "RgbaGet5551", oslua_drawing_RgbaGet5551 },
    { "RgbGet5650", oslua_drawing_RgbGet5650 },
    { "DrawLine", oslua_drawing_DrawLine },
    { "DrawRect", oslua_drawing_DrawRect },
    { "DrawFillRect", oslua_drawing_DrawFillRect },
    { "DrawGradientRect", oslua_drawing_DrawGradientRect },
    { NULL, NULL }
};

LUALIB_API int luaopen_oslua_drawing(lua_State *L) {
    luaL_register(L, "osl.drawing", oslua_drawing_lib);
    return 1;
}
