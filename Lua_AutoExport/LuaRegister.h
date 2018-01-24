#pragma once

#include <typeinfo>
#include "lua.hpp"


/****************************************************************************************************************
*
*    Brief   : 全局函数导入Lua。
*
****************************************************************************************************************/
template <typename FUNCTION>
void LuaRegisterFunction(lua_State* L, FUNCTION func, const char* pFuncName)
{
	int size = sizeof(func);
	void* pUD = lua_newuserdata(L, size);
	memcpy(pUD, &func, size);

	lua_pushcclosure(L, LuaFunctionCallProxy<FUNCTION>::CallProxy, 1);
	lua_setglobal(L, pFuncName);
}


/****************************************************************************************************************
*
*    Brief   : Cpp类导入Lua。
*
****************************************************************************************************************/
template <typename CLASS>
class LuaRegisterClass
{
public:
	LuaRegisterClass(lua_State* L)
	{
		_L = L;
	}
	~LuaRegisterClass()
	{

	}

	void Begin()
	{
		lua_newtable(_L);
		int tableIndex = lua_gettop(_L);

		const char* pMetaTableName = GetClassName<CLASS>();
		luaL_newmetatable(_L, pMetaTableName);
		int metaTableIndex = lua_gettop(_L);

		lua_pushliteral(_L, "__metatable");
		lua_pushvalue(_L, tableIndex);
		lua_rawset(_L, metaTableIndex);

		lua_pushliteral(_L, "__index");
		lua_pushvalue(_L, tableIndex);
		lua_rawset(_L, metaTableIndex);

		lua_pushliteral(_L, "__gc");
		lua_pushcfunction(_L, LuaRegisterClass<CLASS>::Destroy);
		lua_rawset(_L, metaTableIndex);

		lua_pop(_L, 1);
	}

	template <typename FUNCTION>
	void Export(FUNCTION func, const char* pFuncName)
	{
		int size = sizeof(func);
		void* data = lua_newuserdata(_L, size);
		memcpy(data, &func, size);

		lua_pushcclosure(_L, LuaClassCallProxy<CLASS, FUNCTION>::CallProxy, 1);
		lua_setfield(_L, -2, pFuncName);
	}

	void End()
	{
		lua_pop(_L, 1);

		const char* pClassName = GetClassName<CLASS>();
		lua_register(_L, pClassName, LuaRegisterClass<CLASS>::Create);
	}

	static int Create(lua_State* L)
	{
		int id = lua_tointeger(L, 1);
		const char* pName = lua_tostring(L, 2);
		lua_pop(L, 2);

		CLASS* pObj = new CLASS(id, pName);
		CLASS** pUD = (CLASS**)lua_newuserdata(L, sizeof(CLASS*));
		*pUD = pObj;

		const char* pClassName = GetClassName<CLASS>();
		luaL_getmetatable(L, pClassName);
		lua_setmetatable(L, -2);

		return 1;
	}

	static int Destroy(lua_State* L)
	{
		CLASS* pObj = *(CLASS**)lua_touserdata(L, 1);
		delete pObj;
		return 0;
	}

private:

	lua_State* _L;
};


/****************************************************************************************************************
 *
 *    Brief   : 全局函数函数代理。
 *
 ****************************************************************************************************************/
template <typename FUNCTION>
class LuaFunctionCallProxy
{
public:
	static int CallProxy(lua_State* L)
	{
		FUNCTION func = *(FUNCTION*)lua_touserdata(L, lua_upvalueindex(1));
		return LuaFunctionCallDispatcher::Dispatch(L, func);
	}
};


/****************************************************************************************************************
 *
 *    Brief   : Cpp类函数代理。
 *
 ****************************************************************************************************************/
template <typename CLASS, typename FUNCTION>
class LuaClassCallProxy
{
public:
	static int CallProxy(lua_State* L)
	{
		FUNCTION func = *(FUNCTION*)lua_touserdata(L, lua_upvalueindex(1));

		const char* pClassName = GetClassName<CLASS>();
		luaL_checktype(L, 1, LUA_TUSERDATA);
		void* pUD = luaL_checkudata(L, 1, pClassName);
		CLASS* pObj = *(CLASS**)pUD;

		//提取函数的参数和返回值。
		return LuaClassCallDispatcher<CLASS>::Dispatch(L, pObj, func);
	}
};


/****************************************************************************************************************
 *
 *    Brief   : 全局函数返回值与参数提取。
 *
 ****************************************************************************************************************/
class LuaFunctionCallDispatcher
{
public:
	template <typename RET>
	static int Dispatch(lua_State* L, RET(* func)())
	{
		return LuaFunctionCaller<RET>::Call(L, func);
	}

	template <typename RET, typename P1>
	static int Dispatch(lua_State* L, RET(* func)(P1))
	{
		return LuaFunctionCaller<RET>::Call(L, func);
	}

	template <typename RET, typename P1, typename P2>
	static int Dispatch(lua_State* L, RET(* func)(P1, P2))
	{
		return LuaFunctionCaller<RET>::Call(L, func);
	}
};


/****************************************************************************************************************
 *
 *    Brief   : Cpp类函数返回值与参数提取。
 *
 ****************************************************************************************************************/
template <typename CLASS>
class LuaClassCallDispatcher
{
public:
	template <typename RET>
	static int Dispatch(lua_State* L, CLASS* pObj, RET(CLASS::* func)())
	{
		return LuaClassCaller<CLASS, RET>::Call(L, pObj, func);
	}

	template <typename RET, typename P1>
	static int Dispatch(lua_State* L, CLASS* pObj, RET(CLASS::* func)(P1))
	{
		return LuaClassCaller<CLASS, RET>::Call(L, pObj, func);
	}

	template <typename RET, typename P1, typename P2>
	static int Dispatch(lua_State* L, CLASS* pObj, RET(CLASS::* func)(P1, P2))
	{
		return LuaClassCaller<CLASS, RET>::Call(L, pObj, func);
	}
};


/****************************************************************************************************************
 *
 *    Brief   : 全局函数调用。
 *
 ****************************************************************************************************************/
template <typename RET>
class LuaFunctionCaller
{
public:
	static int Call(lua_State* L, RET(* func)())
	{
		RET ret = (*func)();
		WriteValue(L, ret);
		return 1;
	}

	template <typename P1>
	static int Call(lua_State* L, RET(* func)(P1))
	{
		P1 p1 = ReadValue(TypeHelper<P1>(), L, 1);
		RET ret = (*func)(p1);
		WriteValue(L, ret);
		return 1;
	}

	template <typename P1, typename P2>
	static int Call(lua_State* L, RET(* func)(P1, P2))
	{
		P1 p1 = ReadValue(TypeHelper<P1>(), L, 1);
		P2 p2 = ReadValue(TypeHelper<P2>(), L, 2);
		RET ret = (*func)(p1, p2);
		WriteValue(L, ret);
		return 1;
	}
};

//偏特化处理无返回值
template <>
class LuaFunctionCaller<void>
{
public:
	static int Call(lua_State* L, void(*func)())
	{
		(*func)();
		return 0;
	}

	template <typename P1>
	static int Call(lua_State* L, void(*func)(P1))
	{
		P1 p1 = ReadValue(TypeHelper<P1>(), L, 1);
		(*func)(p1);
		return 0;
	}

	template <typename P1, typename P2>
	static int Call(lua_State* L, void(*func)(P1, P2))
	{
		P1 p1 = ReadValue(TypeHelper<P1>(), L, 1);
		P2 p2 = ReadValue(TypeHelper<P2>(), L, 2);
		(*func)(p1, p2);
		return 0;
	}
};


/****************************************************************************************************************
 *
 *    Brief   : Cpp类函数调用。
 *
 ****************************************************************************************************************/
template <typename CLASS, typename RET>
class LuaClassCaller
{
public:
	static int Call(lua_State* L, CLASS* pObj, RET(CLASS::* func)())
	{
		RET ret = (pObj->*func)();
		WriteValue(L, ret);
		return 1;
	}

	template <typename P1>
	static int Call(lua_State* L, CLASS* pObj, RET(CLASS::* func)(P1))
	{
		P1 p1 = ReadValue(TypeHelper<P1>(), L, 2);
		RET ret = (pObj->*func)(p1);
		WriteValue(L, ret);
		return 1;
	}

	template <typename P1, typename P2>
	static int Call(lua_State* L, CLASS* pObj, RET(CLASS::* func)(P1, P2))
	{
		P1 p1 = ReadValue(TypeHelper<P1>(), L, 2);
		P2 p2 = ReadValue(TypeHelper<P2>(), L, 3);
		RET ret = (pObj->*func)(p1, p2);
		WriteValue(L, ret);
		return 1;
	}
};

//模板偏特化处理无返回值。
template <typename CLASS>
class LuaClassCaller<CLASS, void>
{
public:
	static int Call(lua_State* L, CLASS* pObj, void(CLASS::* func)())
	{
		(pObj->*func)();
		return 0;
	}

	template <typename P1>
	static int Call(lua_State* L, CLASS* pObj, void(CLASS::* func)(P1))
	{
		P1 p1 = ReadValue(TypeHelper<P1>(), L, 2);
		(pObj->*func)(p1);
		return 0;
	}

	template <typename P1, typename P2>
	static int Call(lua_State* L, CLASS* pObj, void(CLASS::* func)(P1, P2))
	{
		P1 p1 = ReadValue(TypeHelper<P1>(), L, 2);
		P2 p2 = ReadValue(TypeHelper<P2>(), L, 3);
		(pObj->*func)(p1, p2);
		return 0;
	}
};


/****************************************************************************************************************
 *
 *    Brief   : 类型辅助类。
 *
 ****************************************************************************************************************/
template <typename CLASS>
struct TypeHelper { };


/****************************************************************************************************************
 *
 *    Brief   : 全局函数。
 *
 ****************************************************************************************************************/
int ReadValue(TypeHelper<int>, lua_State* L, int index)
{
	return lua_tointeger(L, index);
}

const char* ReadValue(TypeHelper<const char*>, lua_State* L, int index)
{
	return lua_tostring(L, index);
}

void WriteValue(lua_State* L, int value)
{
	lua_pushinteger(L, value);
}

void WriteValue(lua_State* L, const char* value)
{
	lua_pushstring(L, value);
}

template <typename CLASS>
const char* GetClassName()
{
	///pClass = "class XXX", 需要去出前6个字符"class ",返回"XXX"的地址。
	const char* pClazz = typeid(CLASS).name();
	return pClazz + 6;
}





