#include "XUIObject.h"


namespace Smile
{
	void OnClick(XUIObject& obj)
	{
		//��ӡ��־
		wchar_t title[32];
		swprintf(title, L"Info: �����UI!");
		XLog::AddString(title);
	}
}