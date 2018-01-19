#include <iostream>

#include "Dump.h"

int gcFunction(lua_State* L)
{
	return 1;
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	//创建一个Table
	lua_newtable(L);
	int tableIndex = lua_gettop(L);
	DumpStack(L);


	//创建一个元表
	luaL_newmetatable(L, "MyMetaTable");
	int metaTableIndex = lua_gettop(L);
	DumpStack(L);

	//创建元彪元素 - "__metatable"
	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, tableIndex);
	DumpStack(L);
	lua_rawset(L, metaTableIndex);
	DumpStack(L);

	//创建元彪元素 - "__index"
	lua_pushliteral(L, "__index");
	lua_pushvalue(L, tableIndex);
	DumpStack(L);
	lua_rawset(L, metaTableIndex);
	DumpStack(L);

	//创建元彪元素 - "__gc"
	lua_pushliteral(L, "__gc");
	lua_pushcfunction(L, gcFunction);
	DumpStack(L);
	lua_rawset(L, metaTableIndex);
	DumpStack(L);


	lua_close(L);

	system("pause");
	return 0;
}