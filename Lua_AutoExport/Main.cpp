#include <iostream>

#include "Dump.h"
#include "LuaRegister.h"
#include "XHero.h"

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

	//����ȫ�ֺ���
	LuaRegisterFunction(L, GlobalTest, "GlobalTest");

	//������
	LuaRegisterClass<XHero> reg(L);
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