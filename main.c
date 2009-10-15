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

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pspsdk.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <psputility.h>

#include "oslib.h"

#define printf pspDebugScreenPrintf

int SetupCallbacks(void);

LUALIB_API int luaopen_oslua_general(lua_State *L);
LUALIB_API int luaopen_oslua_drawing(lua_State *L);
LUALIB_API int luaopen_oslua_images(lua_State *L);
LUALIB_API int luaopen_oslua_audio(lua_State *L);
LUALIB_API int luaopen_oslua_controller(lua_State *L);
LUALIB_API int luaopen_oslua_dialog(lua_State *L);
LUALIB_API int luaopen_oslua_network(lua_State *L);
LUALIB_API int luaopen_oslua_math(lua_State *L);
LUALIB_API int luaopen_oslua_message(lua_State *L);
LUALIB_API int luaopen_oslua_text(lua_State *L);

LUALIB_API int luaopen_libfs(lua_State *L);

char cwd[1024];
lua_State *globalL;

int main(void)
{
    int success = 0;
    char scriptpath[1024];
    lua_State *L = globalL;

    SetupCallbacks();

    getcwd(cwd, 1024);

    oslInit(OSL_IF_USEOWNCALLBACKS);
    oslInitGfx(OSL_PF_8888, 1);
    oslInitAudio();
    oslInitAudioME(OSL_FMT_ALL);
    oslIntraFontInit(INTRAFONT_CACHE_MED | INTRAFONT_STRING_UTF8);
    oslSetQuitOnLoadFailure(1);

    L = luaL_newstate();

    luaL_openlibs(L);
    luaopen_oslua_general(L);
    luaopen_oslua_drawing(L);
    luaopen_oslua_images(L);
    luaopen_oslua_audio(L);
    luaopen_oslua_controller(L);
    luaopen_oslua_dialog(L);
    luaopen_oslua_network(L);
    luaopen_oslua_math(L);
    luaopen_oslua_message(L);
    luaopen_oslua_text(L);
    luaopen_libfs(L);

    strcpy(scriptpath, cwd);
    strcat(scriptpath, "/script.lua");

    {
        if(luaL_loadfile(L, scriptpath)) {
            //pspDebugScreenInit();
            //printf("Couldn't load file: %s\n", lua_tostring(L, -1));
            //printf("\nPress START to exit");
            oslFatalError("Couldn't load file: %s\n", lua_tostring(L, -1));
        } else {
            if(lua_pcall(L, 0, LUA_MULTRET, 0)) {
                //pspDebugScreenInit();
                //printf("Failed to run script: %s\n", lua_tostring(L, -1));
                //printf("\nPress START to exit");
                oslFatalError("Failed to run script: %s\n", lua_tostring(L, -1));
            } else {
                success = 1;
            }
        }
        oslFlushKey();
    }
    //while(!success && oslWaitKey() != OSL_KEY_START);

    lua_close(L);

    osl_quit = 1;
    oslIntraFontShutdown();
    oslDeinitAudio();
    oslEndGfx();
    oslQuit();

    return 0;
}
/*
int module_start(SceSize argc, void *argp) {
    SceUID thid = sceKernelCreateThread("User Thread", (int (*)(SceSize, void*))main_thread, 0x12, 12 * 1024, PSP_THREAD_ATTR_USER | THREAD_ATTR_VFPU, NULL);
    sceKernelStartThread(thid, 0, 0);
    sceKernelWaitThreadEnd(thid, NULL);
    return 0;
}

int module_stop(SceSize argc, void *argp) {
	return 0;
}
*/
