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

/* Handled globally
static int oslua_audio_InitAudio(lua_State *L) {
    lua_pushnumber(L, oslInitAudio());
    return 1;
}

static int oslua_audio_DeinitAudio(lua_State *L) {
    oslDeinitAudio();
    return 1;
}

static int oslua_audio_InitAudioME(lua_State *L) {
    oslInitAudioME(checkoslua_audiomeformat(L, 1));
    return 1;
}
*/

static int oslua_audio_LoadSoundFile(lua_State *L) {
    const char *filename = luaL_checkstring(L, 1);
    int stream = checkoslua_streamformat(L, 2);
    OSL_SOUND *s = oslLoadSoundFile(filename, stream);
    if(s) {
        pushoslua_sound(L, s);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static int oslua_audio_LoadSoundFileWAV(lua_State *L) {
    const char *filename = luaL_checkstring(L, 1);
    int stream = checkoslua_streamformat(L, 2);
    OSL_SOUND *s = oslLoadSoundFileWAV(filename, stream);
    if(s) {
        pushoslua_sound(L, s);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static int oslua_audio_LoadSoundFileBGM(lua_State *L) {
    const char *filename = luaL_checkstring(L, 1);
    int stream = checkoslua_streamformat(L, 2);
    OSL_SOUND *s = oslLoadSoundFileBGM(filename, stream);
    if(s) {
        pushoslua_sound(L, s);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static int oslua_audio_LoadSoundFileMOD(lua_State *L) {
    const char *filename = luaL_checkstring(L, 1);
    int stream = checkoslua_streamformat(L, 2);
    if(stream == OSL_FMT_NONE) {
        OSL_SOUND *s = oslLoadSoundFileMOD(filename, stream);
        if(s) {
            pushoslua_sound(L, s);
        } else {
            lua_pushnil(L);
        }
    } else {
        lua_pushstring(L, "stream must be FMT_NONE");
        lua_error(L);
    }
    return 1;
}

static int oslua_audio_LoadSoundFileMP3(lua_State *L) {
    const char *filename = luaL_checkstring(L, 1);
    int stream = checkoslua_streamformat(L, 2);
    OSL_SOUND *s = oslLoadSoundFileMP3(filename, stream);
    if(s) {
        pushoslua_sound(L, s);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static int oslua_audio_LoadSoundFileAT3(lua_State *L) {
    const char *filename = luaL_checkstring(L, 1);
    int stream = checkoslua_streamformat(L, 2);
    OSL_SOUND *s = oslLoadSoundFileAT3(filename, stream);
    if(s) {
        pushoslua_sound(L, s);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static int oslua_audio_SetModSampleRate(lua_State *L) {
    int freq = luaL_checkint(L, 1);
    int stereo = luaL_checkint(L, 2);
    int shift = luaL_checkint(L, 3);
    if(stereo == 1) {
        oslSetModSampleRate(freq, stereo, shift);
    } else {
        luaL_error(L, "stereo MUST be 1");
    }
    return 1;
}

int oslua_audio_SetSoundLoop(lua_State *L) {
    if(lua_isboolean(L, 2)) {
        oslSetSoundLoop(checkoslua_sound(L, 1), lua_toboolean(L, 2));
    } else {
        luaL_typerror(L, 2, "boolean");
        lua_error(L);
    }
    return 1;
}

int oslua_audio_PlaySound(lua_State *L) {
    OSL_SOUND *s = checkoslua_sound(L, 1);
    int voice = luaL_checkint(L, 2);
    oslPlaySound(s, voice);
    return 1;
}

int oslua_audio_StopSound(lua_State *L) {
    oslStopSound(checkoslua_sound(L, 1));
    return 1;
}

int oslua_audio_PauseSound(lua_State *L) {
    oslPauseSound(checkoslua_sound(L, 1), luaL_checkint(L, 2));
    return 1;
}

int oslua_audio_DeleteSound(lua_State *L) {
    oslDeleteSound(checkoslua_sound(L, 1));
    return 1;
}

static int oslua_audio_AudioVSync(lua_State *L) {
    oslAudioVSync();
    return 1;
}

int oslua_audio_GetSoundChannel(lua_State *L) {
    lua_pushinteger(L, oslGetSoundChannel(checkoslua_sound(L, 1)));
    return 1;
}

static const luaL_reg oslua_audio_lib[] = {
    // handle globally { "InitAudio", oslua_audio_InitAudio },
    // handle globally { "DeinitAudio", oslua_audio_DeinitAudio },
    // handle globally { "InitAudioME", oslua_audio_InitAudioME },
    { "LoadSoundFile", oslua_audio_LoadSoundFile },
    { "LoadSoundFileWAV", oslua_audio_LoadSoundFileWAV },
    { "LoadSoundFileBGM", oslua_audio_LoadSoundFileBGM },
    { "LoadSoundFileMOD", oslua_audio_LoadSoundFileMOD },
    { "LoadSoundFileMP3", oslua_audio_LoadSoundFileMP3 },
    { "LoadSoundFileAT3", oslua_audio_LoadSoundFileAT3 },
    { "SetModSampleRate", oslua_audio_SetModSampleRate },
    { "SetSoundLoop", oslua_audio_SetSoundLoop },
    { "PlaySound", oslua_audio_PlaySound },
    { "StopSound", oslua_audio_StopSound },
    { "PauseSound", oslua_audio_PauseSound },
    // handled by __gc { "DeleteSound", oslua_audio_DeleteSound },
    { "AudioVSync", oslua_audio_AudioVSync },
    { "GetSoundChannel", oslua_audio_GetSoundChannel },
    { NULL, NULL }
};

LUALIB_API int luaopen_oslua_audio(lua_State *L) {
    luaL_register(L, "osl.audio", oslua_audio_lib);
    return 1;
}
