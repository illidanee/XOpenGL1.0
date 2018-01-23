#pragma once

#include <iostream>
#include "lua.hpp"

/****************************************************************************************************************
*
*    Brief   : ȫ�ֺ���������-��ӡLuaջ��Ϣ��
*
****************************************************************************************************************/
void DumpStack(lua_State* L);
void DumpInfo(lua_State* L, int i);

void DumpTable(lua_State* L, int i);
void DumpTableHeader(lua_State* L, int i);
void DumpTableBody(lua_State* L, int i);