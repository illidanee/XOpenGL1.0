#include <iostream>

#include "Dump.h"
#include "LuaRegister.h"
#include "XHero.h"

int id = 125;

char buff[128] = { 0 };
const char* GlobalTest(int i)
{
	//char buff[128] = { 0 };				//使用局部变量返回给lua时，当lua拿到该地址时，该地址对象已经销毁。
	sprintf(buff, "AutoExport : %d", i);
	return buff;
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	//导出全局变量
	LuaRegisterVariable<int>(L, id, "id");

	//导出全局函数
	LuaRegisterFunction(L, GlobalTest, "GlobalTest");

	//导出类
	LuaRegisterClass<XHero> reg(L);
	reg.Begin();
	reg.ExportVariable(id, "id");
	reg.ExportFunction(&XHero::GetName, "GetName");
	reg.ExportFunction(&XHero::SetName, "SetName");
	reg.ExportFunction(&XHero::GetAge, "GetAge");
	reg.ExportFunction(&XHero::SetAge, "SetAge");
	reg.End();

	luaL_dofile(L, "main.lua");

	lua_close(L);

	system("pause");
	return 0;
}