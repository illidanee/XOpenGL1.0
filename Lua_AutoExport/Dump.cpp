#include "Dump.h"

/****************************************************************************************************************
*
*    Brief   : 全局函数-打印Lua栈信息。
*
****************************************************************************************************************/
void DumpStack(lua_State* L)
{
	int num = lua_gettop(L);
	printf("元素个数：[%05d] <<--------------------------------------------------------------------------------------------\n", num);
	for (int i = 1; i <= num; ++i)
	{
		DumpInfo(L, i);
	}
}

void DumpInfo(lua_State* L, int i)
{
	int type = lua_type(L, i);
	const char* typeName = lua_typename(L, type);
	printf("TypeName: %s", typeName);

	switch (type)
	{
	case LUA_TBOOLEAN:
	{
		const char* str = lua_toboolean(L, i) ? "true" : "false";
		printf("[%s]\n", str);
	}
	break;
	case LUA_TNUMBER:
	{
		double num = lua_tonumber(L, i);
		printf("[%f]\n", num);
	}
	break;
	case LUA_TSTRING:
	{
		const char* str = lua_tostring(L, i);
		printf("[%s]\n", str);
	}
	break;
	case LUA_TTABLE:
	{
		const void * pAddr = lua_topointer(L, i);
		printf("[%p]\n", pAddr);
		DumpTable(L, i);
	}
	break;
	case LUA_TFUNCTION:
	{
		const void * pAddr = lua_topointer(L, i);
		printf("[%p]\n", pAddr);
	}
	break;
	case LUA_TUSERDATA:
	{
		const void * pAddr = lua_topointer(L, i);
		printf("[%p]\n", pAddr);
	}
	break;
	default:
	{
		printf("[Other]\n");
	}
	}
}

void DumpTable(lua_State* L, int i)
{
	lua_pushvalue(L, i);
	printf("{\n");

	lua_pushnil(L);

	while (lua_next(L, -2))
	{
		printf("\t");
		DumpTableHeader(L, -2);
		printf(" = ");
		DumpTableBody(L, -1);
		printf("\n");
		lua_pop(L, 1);
	}
	printf("}\n");

	lua_pop(L, 1);				//注意这个需要弹出一个多余的栈顶元素。
}

void DumpTableHeader(lua_State* L, int i)
{
	int type = lua_type(L, i);
	//const char* typeName = lua_typename(L, type);
	//printf("TypeName: %s", typeName);

	switch (type)
	{
	case LUA_TBOOLEAN:
	{
		const char* str = lua_toboolean(L, i) ? "true" : "false";
		printf("[%s]", str);
	}
	break;
	case LUA_TNUMBER:
	{
		double num = lua_tonumber(L, i);
		printf("[%f]", num);
	}
	break;
	case LUA_TSTRING:
	{
		const char* str = lua_tostring(L, i);
		printf("[%s]", str);
	}
	break;
	case LUA_TTABLE:
	{
		const void * pAddr = lua_topointer(L, i);
		printf("[%p]", pAddr);
	}
	break;
	case LUA_TFUNCTION:
	{
		const void * pAddr = lua_topointer(L, i);
		printf("[%p]", pAddr);
	}
	break;
	case LUA_TUSERDATA:
	{
		const void * pAddr = lua_topointer(L, i);
		printf("[%p]", pAddr);
	}
	break;
	default:
	{
		printf("[Other]");
	}
	}
}

void DumpTableBody(lua_State* L, int i)
{
	int type = lua_type(L, i);
	const char* typeName = lua_typename(L, type);
	printf("TypeName: %s", typeName);

	switch (type)
	{
	case LUA_TBOOLEAN:
	{
		const char* str = lua_toboolean(L, i) ? "true" : "false";
		printf("[%s]", str);
	}
	break;
	case LUA_TNUMBER:
	{
		double num = lua_tonumber(L, i);
		printf("[%f]", num);
	}
	break;
	case LUA_TSTRING:
	{
		const char* str = lua_tostring(L, i);
		printf("[%s]", str);
	}
	break;
	case LUA_TTABLE:
	{
		const void * pAddr = lua_topointer(L, i);
		printf("[%p]", pAddr);
	}
	break;
	case LUA_TFUNCTION:
	{
		const void * pAddr = lua_topointer(L, i);
		printf("[%p]", pAddr);
	}
	break;
	case LUA_TUSERDATA:
	{
		const void * pAddr = lua_topointer(L, i);
		printf("[%p]", pAddr);
	}
	break;
	default:
	{
		printf("[Other]");
	}
	}
}
