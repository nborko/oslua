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

static int oslua_controller_SetKeyAutorepeat(lua_State *L) {
    oslSetKeyAutorepeat(luaL_checknumber(L,1), luaL_checkint(L,2), luaL_checkint(L, 3));
    return 1;
}

static int oslua_controller_SetKeyAutorepeatMask(lua_State *L) {
    oslSetKeyAutorepeatMask(luaL_checknumber(L, 1));
    return 1;
}

static int oslua_controller_SetKeyAutorepeatInit(lua_State *L) {
    oslSetKeyAutorepeatInit(luaL_checkint(L, 1));
    return 1;
}

static int oslua_controller_SetKeyAutorepeatInterval(lua_State *L) {
    oslSetKeyAutorepeatInterval(luaL_checkint(L, 1));
    return 1;
}

static int oslua_controller_SetKeyAnalogToDPad(lua_State *L) {
    int sensitivity = luaL_checkint(L, 1);
    if(sensitivity > 0 && sensitivity < 128) {
        oslSetKeyAnalogToDPad(sensitivity);
    } else {
        luaL_error(L, "sensitivity must be a value from 1 to 127");
    }
    return 1;
}

static int oslua_controller_ReadKeys(lua_State *L) {
    oslReadKeys();
    return 1;
}

typedef struct {
    int key;
    int mask;
} oslua_Keymapping;

static const oslua_Keymapping oslua_keymap[] = {
    { OSL_KEY_SELECT, OSL_KEYMASK_SELECT },
    { OSL_KEY_START, OSL_KEYMASK_START },
    { OSL_KEY_UP, OSL_KEYMASK_UP },
    { OSL_KEY_RIGHT, OSL_KEYMASK_RIGHT },
    { OSL_KEY_DOWN, OSL_KEYMASK_DOWN },
    { OSL_KEY_LEFT, OSL_KEYMASK_LEFT },
    { OSL_KEY_L, OSL_KEYMASK_L },
    { OSL_KEY_R, OSL_KEYMASK_R },
    { OSL_KEY_TRIANGLE, OSL_KEYMASK_TRIANGLE },
    { OSL_KEY_CIRCLE, OSL_KEYMASK_CIRCLE },
    { OSL_KEY_CROSS, OSL_KEYMASK_CROSS },
    { OSL_KEY_SQUARE, OSL_KEYMASK_SQUARE },
    { OSL_KEY_HOME, OSL_KEYMASK_HOME },
    { OSL_KEY_HOLD, OSL_KEYMASK_HOLD },
    { OSL_KEY_NOTE, OSL_KEYMASK_NOTE },
    { 0, 0 }
};

int getKeymaskFromStack(lua_State *L) {
    int argc, i, keymask = 0;
    for(argc = lua_gettop(L); argc; argc--) {
        for(i = 0; oslua_keymap[i].key; i++) {
            if(oslua_keymap[i].key == checkoslua_key(L, argc)) {
                keymask |= oslua_keymap[i].mask;
                break;
            }
        }
    }
    return keymask;
}

static int oslua_controller_KeyPressed(lua_State *L) {
    int keymask = getKeymaskFromStack(L);
    lua_pushboolean(L, osl_pad.pressed.value & keymask);
    return 1;
}

static int oslua_controller_KeyReleased(lua_State *L) {
    int keymask = getKeymaskFromStack(L);
    lua_pushboolean(L, osl_pad.released.value & keymask);
    return 1;
}

static int oslua_controller_KeyHeld(lua_State *L) {
    int keymask = getKeymaskFromStack(L);
    lua_pushboolean(L, osl_pad.held.value & keymask);
    return 1;
}

static int oslua_controller_SetHoldForAnalog(lua_State *L) {
    if(lua_isboolean(L, 1)) {
        oslSetHoldForAnalog(lua_toboolean(L, 1));
    } else {
        luaL_typerror(L, 1, "boolean");
        lua_error(L);
    }
    return 1;
}

static int oslua_controller_WaitKey(lua_State *L) {
    pushoslua_key(L, oslWaitKey());
    return 1;
}

static int oslua_controller_Kbhit(lua_State *L) {
    pushoslua_key(L, oslKbhit());
    return 1;
}
static int oslua_controller_FlushKey(lua_State *L) {
    oslFlushKey();
    return 1;
}

static const luaL_reg oslua_controller_lib[] = {
    { "SetKeyAutorepeat", oslua_controller_SetKeyAutorepeat },
    { "SetKeyAutorepeatMask", oslua_controller_SetKeyAutorepeatMask },
    { "SetKeyAutorepeatInit", oslua_controller_SetKeyAutorepeatInit },
    { "SetKeyAutorepeatInterval", oslua_controller_SetKeyAutorepeatInterval },
    { "SetKeyAnalogToDPad", oslua_controller_SetKeyAnalogToDPad },
    { "ReadKeys", oslua_controller_ReadKeys },
    { "KeyPressed", oslua_controller_KeyPressed },
    { "KeyReleased", oslua_controller_KeyReleased },
    { "KeyHeld", oslua_controller_KeyHeld },
    { "SetHoldForAnalog", oslua_controller_SetHoldForAnalog },
    { "WaitKey", oslua_controller_WaitKey },
    { "Kbhit", oslua_controller_Kbhit },
    { "FlushKey", oslua_controller_FlushKey },
    { NULL, NULL }
};

LUALIB_API int luaopen_oslua_controller(lua_State *L) {
    luaL_register(L, "osl.controller", oslua_controller_lib);
    return 1;
}
