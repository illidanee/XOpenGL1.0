#include <iostream>

#include "Dump.h"
#include "LuaRegister.h"
#include "XHero.h"

int id = 125;

char buff[128] = { 0 };
const char* GlobalTest(int i)
{
	//char buff[128] = { 0 };				//ʹ�þֲ��������ظ�luaʱ����lua�õ��õ�ַʱ���õ�ַ�����Ѿ����١�
	sprintf(buff, "AutoExport : %d", i);
	return buff;
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	//����ȫ�ֱ���
	LuaRegisterVariable<int>(L, id, "id");

	//����ȫ�ֺ���
	LuaRegisterFunction(L, GlobalTest, "GlobalTest");

	//������
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