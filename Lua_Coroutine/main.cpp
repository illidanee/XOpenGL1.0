#include <iostream>

#include "lua.hpp"

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	//ִ�е�1��
	luaL_dofile(L, "main.lua");

	//�鿴״̬
	system("pause");
	lua_getglobal(L, "ss");
	lua_call(L, 0, 0);

	//ִ�е�2��
	system("pause");
	lua_getglobal(L, "cc");
	lua_call(L, 0, 0);

	//ִ�е�3��
	system("pause");
	lua_getglobal(L, "cc");
	lua_call(L, 0, 0);

	//ִ�е�4��
	system("pause");
	lua_getglobal(L, "cc");
	lua_call(L, 0, 0);

	//ִ�е�5��
	system("pause");
	lua_getglobal(L, "cc");
	lua_call(L, 0, 0);

	//�鿴״̬
	system("pause");
	lua_getglobal(L, "ss");
	lua_call(L, 0, 0);

	lua_close(L);

	system("pause");
	return 0;
}