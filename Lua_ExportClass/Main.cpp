#include <iostream>

#include "Dump.h"

#include "XHero.h"

/****************************************************************************************************************
 *
 *    Brief   : XHero辅助类 - 创建函数需要注册到全局表中，成员函数需要注册到元表中。
 *
 ****************************************************************************************************************/
class LuaHero
{
public:
	static void Init(lua_State* L)
	{
		//创建Table
		lua_newtable(L);
		int tableIndex = lua_gettop(L);

		//创建MetaTable
		luaL_newmetatable(L, "XHero");
		int metaTableIndex = lua_gettop(L);

		lua_pushliteral(L, "__metatable");
		lua_pushvalue(L, tableIndex);
		lua_rawset(L, metaTableIndex);

		lua_pushliteral(L, "__index");
		lua_pushvalue(L, tableIndex);
		lua_rawset(L, metaTableIndex);

		lua_pushliteral(L, "__gc");
		lua_pushcfunction(L, LuaHero::GC);
		lua_rawset(L, metaTableIndex);

		lua_pop(L, 1);

		//向Table中添加函数或者闭包。
		//lua_pushcclosure(L, LuaHero::SetName, 0);
		lua_pushcfunction(L, LuaHero::SetName);
		lua_setfield(L, -2, "SetName");

		//lua_pushcclosure(L, LuaHero::SetAge, 0);
		lua_pushcfunction(L, LuaHero::SetAge);
		lua_setfield(L, -2, "SetAge");

		lua_pop(L, 1);

		//注册创建函数到Lua
		lua_register(L, "XHero", LuaHero::Create);
	}

	static int Create(lua_State* L)
	{
		//取参数
		int i = lua_tointeger(L, 1);
		char* pName = (char*)lua_tostring(L, 2);
		lua_pop(L, 2);

		//创建用户数据 - 即：XHero对象。
		XHero* pHero = new XHero(i, pName);
		void** pObj = (void**)lua_newuserdata(L, sizeof(void*));
		*pObj = pHero;

		//关联元数据。
		luaL_getmetatable(L, "XHero");
		lua_setmetatable(L, -2);

		return 1;
	}

	static int SetName(lua_State* L)
	{
		//取参数
		void* pUD = luaL_checkudata(L, 1, "XHero");
		XHero* pObj = *(XHero**)pUD;
		char* pName = (char*)lua_tostring(L, 2);
		lua_pop(L, 2);

		//调用方法
		pObj->SetName(pName);

		return 0;
	}

	static int SetAge(lua_State* L)
	{
		//取参数
		void* pUD = luaL_checkudata(L, 1, "XHero");
		XHero* pObj = *(XHero**)pUD;
		int age = lua_tointeger(L, 2);
		lua_pop(L, 2);

		//调用方法
		pObj->SetAge(age);

		return 0;
	}

	static int GC(lua_State *L)
	{
		//取参数
		XHero* pHero = (XHero*)(*(XHero**)lua_touserdata(L, -1));
		lua_pop(L, 1);
		
		//删除对象
		delete pHero;

		return  0;
	}
};

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	//必须先初始化-创建元表并关联，同时注册创建函数。
	LuaHero::Init(L);

	//调用Lua脚本。
	luaL_dofile(L, "main.lua");

	lua_close(L);
	system("puase");
	return 0;
}


