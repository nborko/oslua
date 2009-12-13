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

int oslua_audio_SetSoundLoop(lua_State *L);
int oslua_audio_PlaySound(lua_State *L);
int oslua_audio_StopSound(lua_State *L);
int oslua_audio_PauseSound(lua_State *L);
int oslua_audio_DeleteSound(lua_State *L);
int oslua_audio_GetSoundChannel(lua_State *L);

LUA_USERDATA(oslua_sound)

LUA_GETTER(oslua_sound, filename, lua_pushstring);
LUA_GETTER(oslua_sound, isStreamed, lua_pushboolean);
LUA_GETTER(oslua_sound, volumeLeft, lua_pushinteger);
LUA_SETTER(oslua_sound, volumeLeft, luaL_checkint);
LUA_GETTER(oslua_sound, volumeRight, lua_pushinteger);
LUA_SETTER(oslua_sound, volumeRight, luaL_checkint);

static lua_userdata_member_mapping oslua_sound_getters[] = {
    LUA_GETTER_MAP(oslua_sound, filename),
    LUA_GETTER_MAP(oslua_sound, isStreamed),
    LUA_GETTER_MAP(oslua_sound, volumeLeft),
    LUA_GETTER_MAP(oslua_sound, volumeRight),
    { NULL, NULL }
};

static lua_userdata_member_mapping oslua_sound_setters[] = {
    LUA_SETTER_MAP(oslua_sound, volumeLeft),
    LUA_SETTER_MAP(oslua_sound, volumeRight),
    { NULL, NULL }
};

LUA_GETTER_META_INDEX(oslua_sound, oslua_sound_getters);
LUA_SETTER_META_NEWINDEX(oslua_sound, oslua_sound_setters);

static const luaL_reg oslua_sound_methods[] = {
    { "SetSoundLoop", oslua_audio_SetSoundLoop },
    { "PlaySound", oslua_audio_PlaySound },
    { "StopSound", oslua_audio_StopSound },
    { "PauseSound", oslua_audio_PauseSound },
    { "GetSoundChannel", oslua_audio_GetSoundChannel },
    { NULL, NULL }
};

static const luaL_reg oslua_sound_meta[] = {
    { "__gc", oslua_audio_DeleteSound },
    { NULL, NULL }
};

int oslua_register_sound(lua_State *L) {

    luaL_register(L, "oslua_sound", oslua_sound_methods);
    int methods = lua_gettop(L);

    registeroslua_sound(L);
    luaL_register(L, 0, oslua_sound_meta);
    LUA_REGISTER_GETTERS(oslua_sound, methods);
    LUA_REGISTER_SETTERS(oslua_sound);

    return 1;
}
