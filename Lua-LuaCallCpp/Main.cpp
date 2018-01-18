#include <iostream>

#include "Lua.hpp"
#include "Dump.h"

int Add(lua_State* L)
{
	int a = lua_tointeger(L, 1);
	int b = lua_tointeger(L, 2);
	lua_pop(L, 2);

	lua_pushinteger(L, a + b);

 	return 1;
}

luaL_Reg funcs[] = {
	"CADD1", Add,
	"CADD2", Add,
	"CADD3", Add,
	"CADD4", Add,
	"CADD5", Add,
	"CADD6", Add,
	"CADD7", Add,
	NULL, NULL
};


int RegFuncs(lua_State* L)
{
	luaL_newlib(L, funcs);
	return 1;
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	/****************************************************************************************************************
	 *
	 *    Brief   : ʹ��lua_registerע�ắ����
	 *
	 ****************************************************************************************************************/
	lua_register(L, "CADD", Add);
	luaL_dostring(L, "CADD(111, 222)");
	DumpStack(L);

	/****************************************************************************************************************
	 *
	 *    Brief   : ʹ��luaL_openlib����ע�ắ����
	 *
	 ****************************************************************************************************************/
	luaL_openlib(L, "MyLib", funcs, 0);
	luaL_dostring(L, "MyLib.CADD1(333, 444)");
	DumpStack(L);

	/****************************************************************************************************************
	 *
	 *    Brief   : ʹ��luaL_requiref����ע�ắ���� - ����������Ϊ1��
	 *
	 ****************************************************************************************************************/
	luaL_requiref(L, "MyMod", RegFuncs, 1);
	luaL_dostring(L, "MyMod.CADD1(555, 666)");
	DumpStack(L);

	lua_close(L);

	system("pause");
	return 0;
}