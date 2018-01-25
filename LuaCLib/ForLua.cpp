#include "ForLua.h"

static int Sum(lua_State* L)
{
	double total = 0.0;
	int num = lua_gettop(L);
	for (int i = 1; i <= num; ++i)
	{
		total += lua_tonumber(L, i);
	}
	lua_pushnumber(L, total);
	return 1;
}

static luaL_Reg functions[] = 
{
	{"Sum", Sum},
	{NULL, NULL}
};

int luaopen_LuaCLib(lua_State* L)
{
	luaL_openlib(L, "XYZ", functions, 0);
	//luaL_register(L, "XYZ", functions);
	return 1;
}