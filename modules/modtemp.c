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

static const luaL_reg oslua_MODULE_lib[] = {
    { "", oslua_MODULE_FUNCTION },
    { NULL, NULL }
};

LUALIB_API int luaopen_oslua_MODULE(lua_State *L) {
    luaL_register(L, "osl.MODULE", oslua_MODULE_lib);
    return 1;
}
