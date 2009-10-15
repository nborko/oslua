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

#ifndef __OSLUA_H
#define __OSLUA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "oslib.h"

#include "userdata.h"

typedef unsigned long int oslua_alphafx;
typedef int oslua_audiomeformat;
typedef unsigned long int oslua_color;
typedef unsigned int oslua_dialogbutton;
typedef unsigned int oslua_dialogresult;
typedef unsigned int oslua_dialogstatus;
typedef unsigned int oslua_dialogtype;
typedef OSL_FONT* oslua_font;
typedef int oslua_fonttype;
typedef OSL_IMAGE* oslua_image;
typedef unsigned int oslua_intrafontoption;
typedef int oslua_key;
typedef int oslua_location;
typedef int oslua_mbaction;
typedef int oslua_pftype;
typedef OSL_SOUND* oslua_sound;
typedef int oslua_streamformat;

LUA_USERDATA_PROTO(oslua_alphafx);
LUA_USERDATA_PROTO(oslua_audiomeformat);
LUA_USERDATA_PROTO(oslua_color);
LUA_USERDATA_PROTO(oslua_dialogbutton);
LUA_USERDATA_PROTO(oslua_dialogresult);
LUA_USERDATA_PROTO(oslua_dialogstatus);
LUA_USERDATA_PROTO(oslua_dialogtype);
LUA_USERDATA_PROTO(oslua_font);
LUA_USERDATA_PROTO(oslua_fonttype);
LUA_USERDATA_PROTO(oslua_image);
LUA_USERDATA_PROTO(oslua_intrafontoption);
LUA_USERDATA_PROTO(oslua_key);
LUA_USERDATA_PROTO(oslua_location);
LUA_USERDATA_PROTO(oslua_mbaction);
LUA_USERDATA_PROTO(oslua_pftype);
LUA_USERDATA_PROTO(oslua_sound);
LUA_USERDATA_PROTO(oslua_streamformat);

#ifdef __cplusplus
}
#endif

#endif /* __OSLUA_H */
