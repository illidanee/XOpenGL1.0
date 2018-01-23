#include <iostream>

#include "Dump.h"
#include "LuaRegister.h"
#include "XHero.h"

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	LuaRegister<XHero> reg(L);
	reg.Begin();
	reg.Export(&XHero::GetName, "GetName");
	reg.Export(&XHero::SetName, "SetName");
	reg.Export(&XHero::GetAge, "GetAge");
	reg.Export(&XHero::SetAge, "SetAge");
	reg.End();

	luaL_dofile(L, "main.lua");

	lua_close(L);

	system("pause");
	return 0;
}