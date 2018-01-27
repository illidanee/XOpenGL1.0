
#include <iostream>

#include "lua.hpp"

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_dofile(L, "main.lua");

	lua_close(L);

	system("pause");
	return 0;
}