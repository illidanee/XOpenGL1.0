#include <iostream>

#include "Dump.h"

int Show(lua_State* L)
{
	//获取栈上参数
	int a = lua_tointeger(L, 1);
	int b = lua_tointeger(L, 2);
	lua_pop(L, 2);

	//获取上值（上值在额外的一个栈中）
	int upValue = lua_tointeger(L, lua_upvalueindex(1));
	const char* pStr = lua_tostring(L, lua_upvalueindex(2));
	void* pData = lua_touserdata(L, lua_upvalueindex(3));

	lua_pushinteger(L, a + b);

	return 1;
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	///压栈上值
	lua_pushinteger(L, 100);
	lua_pushstring(L, "abc");
	void* pbuffer = lua_newuserdata(L, 10);
	memcpy(pbuffer, "123456789", 10);
	DumpStack(L);

	//制作闭包
	lua_pushcclosure(L, Show, 3);
	DumpStack(L);

	//设置全局变量
	lua_setglobal(L, "SHOW");
	DumpStack(L);

	//使用Lua调用Cpp
	luaL_dostring(L, "SHOW(200, 300)");

	lua_close(L);

	system("pause");
	return 0;
}
