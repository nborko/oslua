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

#include <string.h>

int oslua_loader(lua_State *L);
int oslua_register_types(lua_State *L);

int lua_QuitOnLoadFailureCallback = 0;

void QuitOnLoadFailureCallback(const char *filename, u32 reserved) {
    lua_State *lua = luaL_newstate();
    if(lua && lua_QuitOnLoadFailureCallback) {
        lua_rawgeti(lua, LUA_REGISTRYINDEX, lua_QuitOnLoadFailureCallback);
        lua_pushstring(lua, filename);
        if(lua_pcall(lua, 1, 0, 0)) {
            oslFatalError(lua_tostring(lua, -1));
            oslQuit();
        }
    } else {
        oslFatalError("Unable to locate the following file: %s\nPlease reinstall the application.", filename);
        oslQuit();
    }
}

int oslua_general_SetQuitOnLoadFailure(lua_State *L) {
    if(lua_isboolean(L, 1)) {
        oslSetQuitOnLoadFailure(lua_toboolean(L, 1));
    } else {
        luaL_typerror(L, 1, "boolean");
        lua_error(L);
    }
    return 1;
}

int oslua_general_SetQuitOnLoadFailureCallback(lua_State *L) {
    if(lua_gettop(L) > 0) {
        if(lua_isfunction(L, 1)) {
            if(lua_QuitOnLoadFailureCallback) {
                luaL_unref(L, LUA_REGISTRYINDEX, lua_QuitOnLoadFailureCallback);
            }
	    lua_QuitOnLoadFailureCallback = luaL_ref(L, LUA_REGISTRYINDEX);
        } else {
            lua_pushstring(L, "a function parameter is required");
            lua_error(L);
        }
    } else {
        luaL_unref(L, LUA_REGISTRYINDEX, lua_QuitOnLoadFailureCallback);
        lua_QuitOnLoadFailureCallback = 0;
    }
    return 1;
}

static int oslua_general_SetFrameskip(lua_State *L) {
    int val = luaL_checkint(L, 1);
    if(val >= 0) {
        oslSetFrameskip(val);
    } else {
        luaL_error(L, "Frameskip cannot be negative");
    }
    return 1;
}

static int oslua_general_SetMaxFrameskip(lua_State *L) {
    int val = luaL_checkint(L, 1);
    if(val >= 0) {
        oslSetMaxFrameskip(val);
    } else {
        luaL_error(L, "MaxFrameskip cannot be negative");
    }
    return 1;
}

static int oslua_general_SetVSync(lua_State *L) {
    int val = luaL_checkint(L, 1);
    if(val >= 0) {
        oslSetVSync(val);
    } else {
        luaL_error(L, "Must be a valid VSync parameter (see oslib documentation)");
    }
    return 1;
}

static int oslua_general_SyncFrame(lua_State *L) {
    lua_pushboolean(L, oslSyncFrame());
    return 1;
}

static int oslua_general_EndFrame(lua_State *L) {
    oslEndFrame();
    return 1;
}

static int oslua_general_SyncFrameEx(lua_State *L) {
    int frameskip = luaL_checkint(L, 1);
    int max_frameskip = luaL_checkint(L, 2);
    int vsync = luaL_checkint(L, 3);
    if(frameskip < 0) {
        luaL_error(L, "frameskip cannot be negative");
    } else if(max_frameskip < 0) {
        luaL_error(L, "max_frameskip cannot be negative");
    } else if(vsync < 0) {
        luaL_error(L, "vsync must be a valid parameter (see oslib documentation)");
    } else {
       lua_pushboolean(L, oslSyncFrameEx(frameskip, max_frameskip, vsync));
    }
    return 1;
}

static int oslua_general_SetFramerate(lua_State *L) {
    int framerate = luaL_checkint(L, 1);
    if(framerate >= 1 && framerate <= 60) {
        oslSetFramerate(framerate);
    } else {
        luaL_error(L, "framerate must be from 1 to 60");
    }
    return 1;
}

static int oslua_general_WaitVSync(lua_State *L) {
    oslWaitVSync();
    return 1;
}

static int oslua_general_quit(lua_State *L) {
    if(lua_gettop(L) > 0) {
        if(lua_isboolean(L, 1)) {
            osl_quit = lua_toboolean(L, 1);
        } else {
            luaL_typerror(L, 1, "boolean");
            lua_error(L);
        }
    }
    lua_pushboolean(L, osl_quit);
    return 1;
}

static int oslua_general_ShowSplashScreen(lua_State *L) {
    int splashType = luaL_checkint(L, 1);
    if(splashType == 1 || splashType == 2) {
        //oslShowSplashScreen(splashType);
    } else {
        luaL_error(L, "splashType must be either 1 or 2");
    }
    return 1;
}

static const luaL_reg oslua_general_lib[] = {
    { "SetQuitOnLoadFailure", oslua_general_SetQuitOnLoadFailure },
    { "SetQuitOnLoadFailureCallback", oslua_general_SetQuitOnLoadFailureCallback },
    { "SetFrameskip", oslua_general_SetFrameskip },
    { "SetMaxFrameskip", oslua_general_SetMaxFrameskip },
    { "SetVSync", oslua_general_SetVSync },
    { "SyncFrame", oslua_general_SyncFrame },
    { "EndFrame", oslua_general_EndFrame },
    { "SyncFrameEx", oslua_general_SyncFrameEx },
    { "SetFramerate", oslua_general_SetFramerate },
    { "WaitVSync", oslua_general_WaitVSync },
    { "quit", oslua_general_quit },
    { "ShowSplashScreen", oslua_general_ShowSplashScreen },
    { NULL, NULL }
};

LUALIB_API int luaopen_oslua_general(lua_State *L) {
    oslSetQuitOnLoadFailureCallback(QuitOnLoadFailureCallback);

    /* add our loader to import oslua modules */
    //lua_getfield(L, LUA_ENVIRONINDEX, "loaders");
/*
    lua_getglobal(L, "package");
    lua_pushliteral(L, "loaders");
    lua_gettable(L, -2);
    int len = lua_objlen(L, -1);
    lua_pushcfunction(L, oslua_loader);
    lua_rawseti(L, -2, len + 1);
    lua_pop(L, -1);
    lua_pop(L, -1);
*/

    oslua_register_types(L);

    luaL_register(L, "osl", oslua_general_lib);

    /* Constants */
    lua_pushstring(L, OSL_VERSION);
    lua_setfield(L, -2, "VERSION");
    lua_pushnumber(L, OSL_NUM_AUDIO_CHANNELS);
    lua_setfield(L, -2, "NUM_AUDIO_CHANNELS");
    lua_pushnumber(L, OSL_VOLUME_MAX);
    lua_setfield(L, -2, "VOLUME_MAX");
    pushoslua_font(L, osl_sceFont);
    lua_setfield(L, -2, "sceFont");

    /* oslua_alphafx */
    pushoslua_alphafx(L, OSL_FX_NONE);
    lua_setfield(L, -2, "FX_NONE");
    pushoslua_alphafx(L, OSL_FX_FLAT);
    lua_setfield(L, -2, "FX_FLAT");
    pushoslua_alphafx(L, OSL_FX_ALPHA);
    lua_setfield(L, -2, "FX_ALPHA");
    pushoslua_alphafx(L, OSL_FX_ADD);
    lua_setfield(L, -2, "FX_ADD");
    pushoslua_alphafx(L, OSL_FX_SUB);
    lua_setfield(L, -2, "FX_SUB");
    pushoslua_alphafx(L, OSL_FX_DEFAULT);
    lua_setfield(L, -2, "FX_DEFAULT");
    pushoslua_alphafx(L, OSL_FX_OPAQUE);
    lua_setfield(L, -2, "FX_OPAQUE");
    pushoslua_alphafx(L, OSL_FX_TINT);
    lua_setfield(L, -2, "FX_TINT");
    pushoslua_alphafx(L, OSL_FX_RGBA);
    lua_setfield(L, -2, "FX_RGBA");
    pushoslua_alphafx(L, OSL_FX_COLOR);
    lua_setfield(L, -2, "FX_COLOR");

    /* oslua_audioformat */
    pushoslua_audiomeformat(L, OSL_FMT_AT3);
    lua_setfield(L, -2, "FMT_AT3");
    pushoslua_audiomeformat(L, OSL_FMT_MP3);
    lua_setfield(L, -2, "FMT_MP3");
    pushoslua_audiomeformat(L, OSL_FMT_ALL);
    lua_setfield(L, -2, "FMT_ALL");

    /* oslua_dialogbutton */
    pushoslua_dialogbutton(L, PSP_UTILITY_MSGDIALOG_RESULT_UNKNOWN1);
    lua_setfield(L, -2, "PSP_UTILITY_MSGDIALOG_RESULT_UNKNOWN1");
    pushoslua_dialogbutton(L, PSP_UTILITY_MSGDIALOG_RESULT_YES);
    lua_setfield(L, -2, "PSP_UTILITY_MSGDIALOG_RESULT_YES");
    pushoslua_dialogbutton(L, PSP_UTILITY_MSGDIALOG_RESULT_NO);
    lua_setfield(L, -2, "PSP_UTILITY_MSGDIALOG_RESULT_NO");
    pushoslua_dialogbutton(L, PSP_UTILITY_MSGDIALOG_RESULT_BACK);
    lua_setfield(L, -2, "PSP_UTILITY_MSGDIALOG_RESULT_BACK");

    /* oslua_dialogresult */
    pushoslua_dialogresult(L, OSL_DIALOG_CANCEL);
    lua_setfield(L, -2, "DIALOG_CANCEL");
    pushoslua_dialogresult(L, OSL_DIALOG_OK);
    lua_setfield(L, -2, "DIALOG_OK");

    /* oslua_dialogstatus */
    pushoslua_dialogstatus(L, PSP_UTILITY_DIALOG_NONE);
    lua_setfield(L, -2, "PSP_UTILITY_DIALOG_NONE");
    pushoslua_dialogstatus(L, PSP_UTILITY_DIALOG_INIT);
    lua_setfield(L, -2, "PSP_UTILITY_DIALOG_INIT");
    pushoslua_dialogstatus(L, PSP_UTILITY_DIALOG_VISIBLE);
    lua_setfield(L, -2, "PSP_UTILITY_DIALOG_VISIBLE");
    pushoslua_dialogstatus(L, PSP_UTILITY_DIALOG_QUIT);
    lua_setfield(L, -2, "PSP_UTILITY_DIALOG_QUIT");
    pushoslua_dialogstatus(L, PSP_UTILITY_DIALOG_FINISHED);
    lua_setfield(L, -2, "PSP_UTILITY_DIALOG_FINISHED");

    /* oslua_dialogtype */
    pushoslua_dialogtype(L, OSL_DIALOG_NONE);
    lua_setfield(L, -2, "DIALOG_NONE");
    pushoslua_dialogtype(L, OSL_DIALOG_MESSAGE);
    lua_setfield(L, -2, "DIALOG_MESSAGE");
    pushoslua_dialogtype(L, OSL_DIALOG_ERROR);
    lua_setfield(L, -2, "DIALOG_ERROR");
    pushoslua_dialogtype(L, OSL_DIALOG_NETCONF);
    lua_setfield(L, -2, "DIALOG_NETCONF");

    /* oslua_fonttype */
    pushoslua_fonttype(L, OSL_FONT_OFT);
    lua_setfield(L, -2, "FONT_OFT");
    pushoslua_fonttype(L, OSL_FONT_INTRA);
    lua_setfield(L, -2, "FONT_INTRA");

    /* oslua_intrafontoption */
    pushoslua_intrafontoption(L, 0);
    lua_setfield(L, -2, "INTRAFONT_NONE");
    pushoslua_intrafontoption(L, INTRAFONT_ADVANCE_H);
    lua_setfield(L, -2, "INTRAFONT_ADVANCE_H");
    pushoslua_intrafontoption(L, INTRAFONT_ADVANCE_V);
    lua_setfield(L, -2, "INTRAFONT_ADVANCE_V");
    pushoslua_intrafontoption(L, INTRAFONT_ALIGN_LEFT);
    lua_setfield(L, -2, "INTRAFONT_ALIGN_LEFT");
    pushoslua_intrafontoption(L, INTRAFONT_ALIGN_CENTER);
    lua_setfield(L, -2, "INTRAFONT_ALIGN_CENTER");
    pushoslua_intrafontoption(L, INTRAFONT_ALIGN_RIGHT);
    lua_setfield(L, -2, "INTRAFONT_ALIGN_RIGHT");
    pushoslua_intrafontoption(L, INTRAFONT_WIDTH_VAR);
    lua_setfield(L, -2, "INTRAFONT_WIDTH_VAR");
    pushoslua_intrafontoption(L, INTRAFONT_WIDTH_FIX);
    lua_setfield(L, -2, "INTRAFONT_WIDTH_FIX");
    pushoslua_intrafontoption(L, INTRAFONT_ACTIVE);
    lua_setfield(L, -2, "INTRAFONT_ACTIVE");
    pushoslua_intrafontoption(L, INTRAFONT_STRING_ASCII);
    lua_setfield(L, -2, "INTRAFONT_STRING_ASCII");
    pushoslua_intrafontoption(L, INTRAFONT_STRING_SJIS);
    lua_setfield(L, -2, "INTRAFONT_STRING_SJIS");
    pushoslua_intrafontoption(L, INTRAFONT_STRING_UTF8);
    lua_setfield(L, -2, "INTRAFONT_STRING_UTF8");
    pushoslua_intrafontoption(L, INTRAFONT_CACHE_MED);
    lua_setfield(L, -2, "INTRAFONT_CACHE_MED");
    pushoslua_intrafontoption(L, INTRAFONT_CACHE_LARGE);
    lua_setfield(L, -2, "INTRAFONT_CACHE_LARGE");
    pushoslua_intrafontoption(L, INTRAFONT_CACHE_ASCII);
    lua_setfield(L, -2, "INTRAFONT_CACHE_ASCII");
    pushoslua_intrafontoption(L, INTRAFONT_CACHE_ALL);
    lua_setfield(L, -2, "INTRAFONT_CACHE_ALL");

    /* oslua_key */
    pushoslua_key(L, OSL_KEY_SELECT);
    lua_setfield(L, -2, "KEY_SELECT");
    pushoslua_key(L, OSL_KEY_START);
    lua_setfield(L, -2, "KEY_START");
    pushoslua_key(L, OSL_KEY_UP);
    lua_setfield(L, -2, "KEY_UP");
    pushoslua_key(L, OSL_KEY_RIGHT);
    lua_setfield(L, -2, "KEY_RIGHT");
    pushoslua_key(L, OSL_KEY_DOWN);
    lua_setfield(L, -2, "KEY_DOWN");
    pushoslua_key(L, OSL_KEY_LEFT);
    lua_setfield(L, -2, "KEY_LEFT");
    pushoslua_key(L, OSL_KEY_L);
    lua_setfield(L, -2, "KEY_L");
    pushoslua_key(L, OSL_KEY_R);
    lua_setfield(L, -2, "KEY_R");
    pushoslua_key(L, OSL_KEY_TRIANGLE);
    lua_setfield(L, -2, "KEY_TRIANGLE");
    pushoslua_key(L, OSL_KEY_CIRCLE);
    lua_setfield(L, -2, "KEY_CIRCLE");
    pushoslua_key(L, OSL_KEY_CROSS);
    lua_setfield(L, -2, "KEY_CROSS");
    pushoslua_key(L, OSL_KEY_SQUARE);
    lua_setfield(L, -2, "KEY_SQUARE");
    pushoslua_key(L, OSL_KEY_HOME);
    lua_setfield(L, -2, "KEY_HOME");
    pushoslua_key(L, OSL_KEY_HOLD);
    lua_setfield(L, -2, "KEY_HOLD");
    pushoslua_key(L, OSL_KEY_NOTE);
    lua_setfield(L, -2, "KEY_NOTE");

    /* oslua_location */
    pushoslua_location(L, OSL_IN_NONE);
    lua_setfield(L, -2, "IN_NONE");
    pushoslua_location(L, OSL_IN_VRAM);
    lua_setfield(L, -2, "IN_VRAM");
    pushoslua_location(L, OSL_IN_RAM);
    lua_setfield(L, -2, "IN_RAM");
    pushoslua_location(L, OSL_LOCATION_MASK);
    lua_setfield(L, -2, "LOCATION_MASK");
    pushoslua_location(L, OSL_SWIZZLED);
    lua_setfield(L, -2, "SWIZZLED");
    pushoslua_location(L, OSL_UNSWIZZLED);
    lua_setfield(L, -2, "UNSWIZZLED");

    /* oslua_mbaction */
    pushoslua_mbaction(L, OSL_MB_OK);
    lua_setfield(L, -2, "MB_OK");
    pushoslua_mbaction(L, OSL_MB_CANCEL);
    lua_setfield(L, -2, "MB_CANCEL");
    pushoslua_mbaction(L, OSL_MB_YES);
    lua_setfield(L, -2, "MB_YES");
    pushoslua_mbaction(L, OSL_MB_NO);
    lua_setfield(L, -2, "MB_NO");
    pushoslua_mbaction(L, OSL_MB_QUIT);
    lua_setfield(L, -2, "MB_QUIT");

    /* oslua_pftype */
    pushoslua_pftype(L, OSL_PF_5650);
    lua_setfield(L, -2, "PF_5650");
    pushoslua_pftype(L, OSL_PF_5551);
    lua_setfield(L, -2, "PF_5551");
    pushoslua_pftype(L, OSL_PF_4444);
    lua_setfield(L, -2, "PF_4444");
    pushoslua_pftype(L, OSL_PF_8888);
    lua_setfield(L, -2, "PF_8888");
    pushoslua_pftype(L, OSL_PF_4BIT);
    lua_setfield(L, -2, "PF_4BIT");
    pushoslua_pftype(L, OSL_PF_8BIT);
    lua_setfield(L, -2, "PF_8BIT");

    /* oslua_streamformat */
    pushoslua_streamformat(L, OSL_FMT_STREAM);
    lua_setfield(L, -2, "FMT_STREAM");
    pushoslua_streamformat(L, OSL_FMT_NONE);
    lua_setfield(L, -2, "FMT_NONE");

    return 1;
}
