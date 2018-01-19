#include <iostream>

#include "Dump.h"

#include "XHero.h"

/****************************************************************************************************************
 *
 *    Brief   : XHero������ - ����������Ҫע�ᵽȫ�ֱ��У���Ա������Ҫע�ᵽԪ���С�
 *
 ****************************************************************************************************************/
class LuaHero
{
public:
	static void Init(lua_State* L)
	{
		//����Table
		lua_newtable(L);
		int tableIndex = lua_gettop(L);

		//����MetaTable
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

		//��Table����Ӻ������߱հ���
		//lua_pushcclosure(L, LuaHero::SetName, 0);
		lua_pushcfunction(L, LuaHero::SetName);
		lua_setfield(L, -2, "SetName");

		//lua_pushcclosure(L, LuaHero::SetAge, 0);
		lua_pushcfunction(L, LuaHero::SetAge);
		lua_setfield(L, -2, "SetAge");

		lua_pop(L, 1);

		//ע�ᴴ��������Lua
		lua_register(L, "XHero", LuaHero::Create);
	}

	static int Create(lua_State* L)
	{
		//ȡ����
		int i = lua_tointeger(L, 1);
		char* pName = (char*)lua_tostring(L, 2);
		lua_pop(L, 2);

		//�����û����� - ����XHero����
		XHero* pHero = new XHero(i, pName);
		void** pObj = (void**)lua_newuserdata(L, sizeof(void*));
		*pObj = pHero;

		//����Ԫ���ݡ�
		luaL_getmetatable(L, "XHero");
		lua_setmetatable(L, -2);

		return 1;
	}

	static int SetName(lua_State* L)
	{
		//ȡ����
		void* pUD = luaL_checkudata(L, 1, "XHero");
		XHero* pObj = *(XHero**)pUD;
		char* pName = (char*)lua_tostring(L, 2);
		lua_pop(L, 2);

		//���÷���
		pObj->SetName(pName);

		return 0;
	}

	static int SetAge(lua_State* L)
	{
		//ȡ����
		void* pUD = luaL_checkudata(L, 1, "XHero");
		XHero* pObj = *(XHero**)pUD;
		int age = lua_tointeger(L, 2);
		lua_pop(L, 2);

		//���÷���
		pObj->SetAge(age);

		return 0;
	}

	static int GC(lua_State *L)
	{
		//ȡ����
		XHero* pHero = (XHero*)(*(XHero**)lua_touserdata(L, -1));
		lua_pop(L, 1);
		
		//ɾ������
		delete pHero;

		return  0;
	}
};

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	//�����ȳ�ʼ��-����Ԫ��������ͬʱע�ᴴ��������
	LuaHero::Init(L);

	//����Lua�ű���
	luaL_dofile(L, "main.lua");

	lua_close(L);
	system("puase");
	return 0;
}


