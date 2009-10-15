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

static int oslua_math_Sin(lua_State *L) {
    float angle = luaL_checknumber(L, 1);
    float dist = luaL_checknumber(L, 2);
    lua_pushnumber(L, oslSin(angle, dist));
    return 1;
}

static int oslua_math_Cos(lua_State *L) {
    float angle = luaL_checknumber(L, 1);
    float dist = luaL_checknumber(L, 2);
    lua_pushnumber(L, oslCos(angle, dist));
    return 1;
}

static int oslua_math_Sini(lua_State *L) {
    int angle = luaL_checkint(L, 1);
    int dist = luaL_checkint(L, 2);
    lua_pushinteger(L, oslSini(angle, dist));
    return 1;
}

static int oslua_math_Cosi(lua_State *L) {
    int angle = luaL_checkint(L, 1);
    int dist = luaL_checkint(L, 2);
    lua_pushinteger(L, oslCosi(angle, dist));
    return 1;
}

static int oslua_math_GetNextPower2(lua_State *L) {
    lua_pushinteger(L, oslGetNextPower2(luaL_checkint(L, 1)));
    return 1;
}
/*
#define     oslSinf   vfpu_sinf
#define     oslCosf   vfpu_cosf
#define     oslTanf   vfpu_tanf
#define     oslAsinf   vfpu_asinf
#define     oslAcosf   vfpu_acosf
#define     oslAtanf   vfpu_atanf
#define     oslAtan2f   vfpu_atan2f
#define     oslSinhf   vfpu_sinhf
#define     oslCoshf   vfpu_coshf
#define     oslTanhf   vfpu_tanhf
#define     oslSincos   vfpu_sincos
#define     oslExpf   vfpu_expf
#define     oslLogf   vfpu_logf
#define     oslPowf   vfpu_powf
#define     oslFmodf   vf
*/
static int oslua_math_Srand(lua_State *L) {
    oslSrand(luaL_checknumber(L, 1));
    return 1;
}

static int oslua_math_Randf(lua_State *L) {
    lua_pushnumber(L, oslRandf(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
    return 1;
}

static int oslua_math_Rand_8888(lua_State *L) {
    int min = luaL_checkint(L, 1);
    int max = luaL_checkint(L, 2);
    if(min >=0 && min <= 255) {
        if(max >=0 && max <=255 && max >= min) {
            lua_pushinteger(L, oslRand_8888(min, max));
        } else {
            luaL_error(L, "max must be between 0 and 255 and greater than min");
        }
    } else {
        luaL_error(L, "min must be between 0 and 255");
    }
    return 1;
}

static int oslua_math_Sinf(lua_State *L) {
    float angle = luaL_checknumber(L, 1);
    lua_pushnumber(L, oslSinf(angle));
    return 1;
}

static int oslua_math_Cosf(lua_State *L) {
    float angle = luaL_checknumber(L, 1);
    lua_pushnumber(L, oslCosf(angle));
    return 1;
}

static int oslua_math_Tanf(lua_State *L) {
    float angle = luaL_checknumber(L, 1);
    lua_pushnumber(L, oslTanf(angle));
    return 1;
}

static int oslua_math_Asinf(lua_State *L) {
    float angle = luaL_checknumber(L, 1);
    lua_pushnumber(L, oslAsinf(angle));
    return 1;
}

static int oslua_math_Acosf(lua_State *L) {
    float angle = luaL_checknumber(L, 1);
    lua_pushnumber(L, oslAcosf(angle));
    return 1;
}

static int oslua_math_Atanf(lua_State *L) {
    float angle = luaL_checknumber(L, 1);
    lua_pushnumber(L, oslAtanf(angle));
    return 1;
}

static int oslua_math_Atan2f(lua_State *L) {
    lua_pushnumber(L, oslAtan2f(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
    return 1;
}

static int oslua_math_Sinhf(lua_State *L) {
    float angle = luaL_checknumber(L, 1);
    lua_pushnumber(L, oslSinhf(angle));
    return 1;
}

static int oslua_math_Coshf(lua_State *L) {
    float angle = luaL_checknumber(L, 1);
    lua_pushnumber(L, oslCoshf(angle));
    return 1;
}

static int oslua_math_Tanhf(lua_State *L) {
    float angle = luaL_checknumber(L, 1);
    lua_pushnumber(L, oslTanhf(angle));
    return 1;
}

static int oslua_math_Sincos(lua_State *L) {
    float r = luaL_checknumber(L, 1);
    float sin, cos;
    oslSincos(r, &sin, &cos);
    lua_pushnumber(L, sin);
    lua_pushnumber(L, cos);
    return 1;
}

static int oslua_math_Expf(lua_State *L) {
    lua_pushnumber(L, oslExpf(luaL_checknumber(L, 1)));
    return 1;
}

static int oslua_math_Logf(lua_State *L) {
    lua_pushnumber(L, oslLogf(luaL_checknumber(L, 1)));
    return 1;
}

static int oslua_math_Powf(lua_State *L) {
    lua_pushnumber(L, oslPowf(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
    return 1;
}

static int oslua_math_Fmodf(lua_State *L) {
    lua_pushnumber(L, oslFmodf(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
    return 1;
}

static const luaL_reg oslua_math_lib[] = {
    { "sin", oslua_math_Sin },
    { "cos", oslua_math_Cos },
    { "sini", oslua_math_Sini },
    { "cosi", oslua_math_Cosi },
    { "GetNextPower2", oslua_math_GetNextPower2 },
    { "srand", oslua_math_Srand },
    { "randf", oslua_math_Randf },
    { "rand_8888", oslua_math_Rand_8888 },
    { "sinf", oslua_math_Sinf },
    { "cosf", oslua_math_Cosf },
    { "tanf", oslua_math_Tanf },
    { "asinf", oslua_math_Asinf },
    { "acosf", oslua_math_Acosf },
    { "atanf", oslua_math_Atanf },
    { "atan2f", oslua_math_Atan2f },
    { "sinhf", oslua_math_Sinhf },
    { "coshf", oslua_math_Coshf },
    { "tanhf", oslua_math_Tanhf },
    { "sincos", oslua_math_Sincos },
    { "expf", oslua_math_Expf },
    { "logf", oslua_math_Logf },
    { "powf", oslua_math_Powf },
    { "fmodf", oslua_math_Fmodf },
    { NULL, NULL }
};

LUALIB_API int luaopen_oslua_math(lua_State *L) {
    luaL_register(L, "osl.math", oslua_math_lib);
    return 1;
}
