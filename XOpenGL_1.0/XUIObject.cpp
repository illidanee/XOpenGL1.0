#include "XUIObject.h"


namespace Smile
{
	void OnClick(XUIObject& obj)
	{
		//打印日志
		wchar_t title[32];
		swprintf(title, L"Info: 点击了UI!");
		XLog::AddString(title);
	}
}