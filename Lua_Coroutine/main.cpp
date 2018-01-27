#include <iostream>

#include "lua.hpp"

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	//执行第1步
	luaL_dofile(L, "main.lua");

	//查看状态
	system("pause");
	lua_getglobal(L, "ss");
	lua_call(L, 0, 0);

	//执行第2步
	system("pause");
	lua_getglobal(L, "cc");
	lua_call(L, 0, 0);

	//执行第3步
	system("pause");
	lua_getglobal(L, "cc");
	lua_call(L, 0, 0);

	//执行第4步
	system("pause");
	lua_getglobal(L, "cc");
	lua_call(L, 0, 0);

	//执行第5步
	system("pause");
	lua_getglobal(L, "cc");
	lua_call(L, 0, 0);

	//查看状态
	system("pause");
	lua_getglobal(L, "ss");
	lua_call(L, 0, 0);

	lua_close(L);

	system("pause");
	return 0;
}