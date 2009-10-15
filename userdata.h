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

#ifndef __USERDATA_H
#define __USERDATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

/*
 * Basic lua userdata support for TYPE
 * Adapted from http://lua-users.org/wiki/UserDataExample
 * NOTE: All types should be a typedef, and all structs should
 *       be typedefed as pointer types.
 */
#define LUA_USERDATA(TYPE) \
TYPE to##TYPE (lua_State *L, int index) { \
    TYPE *userdata = (TYPE *)lua_touserdata(L, index); \
    if(userdata == NULL) luaL_typerror(L, index, #TYPE); \
    return *userdata; \
} \
TYPE check##TYPE(lua_State *L, int index) { \
    TYPE *userdata; \
    luaL_checktype(L, index, LUA_TUSERDATA); \
    userdata = (TYPE *)luaL_checkudata(L, index, #TYPE); \
    if(userdata == NULL) luaL_typerror(L, index, #TYPE); \
    return *userdata; \
} \
TYPE push##TYPE(lua_State *L, TYPE userdata) { \
    TYPE *newdata = (TYPE *)lua_newuserdata(L, sizeof(TYPE)); \
    luaL_getmetatable(L, #TYPE); \
    lua_setmetatable(L, -2); \
    return *newdata = userdata; \
} \
void register##TYPE(lua_State *L) { \
    luaL_newmetatable(L, #TYPE); \
}

/* prototype definitons for #includes */
#define LUA_USERDATA_PROTO(TYPE) \
TYPE to##TYPE (lua_State *L, int index); \
TYPE check##TYPE(lua_State *L, int index); \
TYPE push##TYPE(lua_State *L, TYPE userdata); \

/*
 * Extended userdata support for getters, setters and
 * methods, based loosely on ideas from:
 * http://lua-users.org/wiki/BindingWithMembersAndMethods
 *
 * The basic idea is that you define each getter as such:
 *     LUA_GETTER(mytype, member_in_struct, function_to_push_data)
 * e.g.
 *     LUA_GETTER(coordinate, x, lua_pushinteger)
 *     LUA_GETTER(coordinate, y, lua_pushinteger)
 * Note that the "push" function could be a userdata function,
 * e.g. pushmytype.
 * 
 * After defining all the getters, then create a mapping, e.g.
 * static lua_userdata_member_mapping coordinate_getters[] = {
 *     LUA_GETTER_MAP(coordinate, x),
 *     LUA_GETTER_MAP(coordinate, y),
 *     { NULL, NULL }
 * };
 *
 * Finally, generate the function for the metatable __index:
 *     LUA_GETTER_META_INDEX(coordinate, coordinate_getters)
 *
 * Register the getters IMMEDIATELY after calling the registerusertype
 * function, e.g.
 *     registercoordinate(L);
 *     LUA_REGISTER_GETTERS(coordinate, 0);
 *
 * The optional METHODS argument can contain a stack position for a
 * previous pushed table of methods, e.g. through luaL_register:
 *     luaL_register(L, "coordinate", coordinate_methods);
 *     int methods = lua_gettop(L);
 *
 * Setters work similarly, and must be registered directly after getters.
 */
typedef struct { \
    const char *field; \
    int (*gsetter)(lua_State *L, void *d); \
} lua_userdata_member_mapping;

int lua_userdata_getter(lua_State *L, void *d, lua_userdata_member_mapping mapping[]);
int lua_userdata_register_getters(lua_State *L, int methods_index, lua_CFunction getter_meta_index);
int lua_userdata_setter(lua_State *L, void *d, lua_userdata_member_mapping mapping[]);
int lua_userdata_register_setters(lua_State *L, lua_CFunction setter_meta_index);

#define LUA_GETTER(TYPE, FIELD, PUSHFUNC) \
int TYPE##_get_##FIELD(lua_State *L, void *d) { \
    PUSHFUNC(L, ((TYPE)d)->FIELD); \
    return 1; \
}

#define LUA_GETTER_MAP(TYPE, FIELD) \
    { #FIELD, TYPE##_get_##FIELD }

#define LUA_GETTER_META_INDEX(TYPE, MAPPING) \
int TYPE##_getter_meta_index(lua_State *L) { \
    return lua_userdata_getter(L, check##TYPE(L, 1), MAPPING); \
}

#define LUA_REGISTER_GETTERS(TYPE, METHODS) \
    lua_userdata_register_getters(L, METHODS, TYPE##_getter_meta_index)

/* setter macros */
#define LUA_SETTER(TYPE, FIELD, POPFUNC) \
int TYPE##_set_##FIELD(lua_State *L, void *d) { \
    ((TYPE)d)->FIELD = POPFUNC(L, 3); \
    return 1; \
}

#define LUA_SETTER_MAP(TYPE, FIELD) \
    { #FIELD, TYPE##_set_##FIELD }

#define LUA_SETTER_META_NEWINDEX(TYPE, MAPPING) \
int TYPE##_setter_meta_newindex(lua_State *L) { \
    return lua_userdata_setter(L, check##TYPE(L, 1), MAPPING); \
}

#define LUA_REGISTER_SETTERS(TYPE) \
    lua_userdata_register_setters(L, TYPE##_setter_meta_newindex)
    
#ifdef __cplusplus
}
#endif

#endif /* __USERDATA_H */
