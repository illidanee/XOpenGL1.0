#pragma once

namespace Smile
{
	class XResource
	{
	public:
		static int LoadTextureFile(const char* pFile, char** pBuffer, int* w, int* h);
	};
}