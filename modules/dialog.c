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

static int oslua_dialog_InitMessageDialog(lua_State *L) {
    const char *message = luaL_checkstring(L, 1);
    if(lua_isboolean(L, 2)) {
        oslInitMessageDialog(message, lua_toboolean(L, 2));
    } else {
        luaL_typerror(L, 2, "boolean");
        lua_error(L);
    }
    return 1;
}

static int oslua_dialog_InitErrorDialog(lua_State *L) {
    unsigned long int error = luaL_checknumber(L, 1);
    if(error >= 0) {
        oslInitErrorDialog(error);
    } else {
        luaL_error(L, "error must be unsigned integer");
    }
    return 1;
}

static int oslua_dialog_DrawDialog(lua_State *L) {
    oslDrawDialog();
    return 1;
}

static int oslua_dialog_GetDialogType(lua_State *L) {
    pushoslua_dialogtype(L, oslGetDialogType());
    return 1;
}

static int oslua_dialog_GetDialogStatus(lua_State *L) {
    pushoslua_dialogstatus(L, oslGetDialogStatus());
    return 1;
}

static int oslua_dialog_GetDialogButtonPressed(lua_State *L) {
    pushoslua_dialogbutton(L, oslGetDialogButtonPressed());
    return 1;
}

static int oslua_dialog_InitNetDialog(lua_State *L) {
    oslInitNetDialog();
    return 1;
}

static int oslua_dialog_DialogGetResult(lua_State *L) {
    pushoslua_dialogresult(L, oslDialogGetResult());
    return 1;
}

static int oslua_dialog_EndDialog(lua_State *L) {
    oslEndDialog();
    return 1;
}

static const luaL_reg oslua_dialog_lib[] = {
    { "InitMessageDialog", oslua_dialog_InitMessageDialog },
    { "InitErrorDialog", oslua_dialog_InitErrorDialog },
    { "DrawDialog", oslua_dialog_DrawDialog },
    { "GetDialogType", oslua_dialog_GetDialogType },
    { "GetDialogStatus", oslua_dialog_GetDialogStatus },
    { "GetDialogButtonPressed", oslua_dialog_GetDialogButtonPressed },
    { "InitNetDialog", oslua_dialog_InitNetDialog },
    { "DialogGetResult", oslua_dialog_DialogGetResult },
    { "EndDialog", oslua_dialog_EndDialog },
    { NULL, NULL }
};

LUALIB_API int luaopen_oslua_dialog(lua_State *L) {
    luaL_register(L, "osl.dialog", oslua_dialog_lib);
    return 1;
}
