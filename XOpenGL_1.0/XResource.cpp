#include "XResource.h"

#include "FreeImage.h"

namespace Smile
{
	int XResource::LoadTextureFile(const char* pFile, char** pBuffer, int* w, int* h)
	{
		FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(pFile, 0);
		if (fif == FIF_UNKNOWN)
			return 0;

		FIBITMAP* dib = FreeImage_Load(fif, pFile);
		
		FIBITMAP* temp = dib;
		dib = FreeImage_ConvertTo32Bits(dib);
		FreeImage_Unload(temp);

		char* tempBuffer = (char*)FreeImage_GetBits(dib);
		*w = FreeImage_GetWidth(dib);
		*h = FreeImage_GetHeight(dib);

		//tempBufferָ����ڴ��ڵ���FreeImage_Unload()����ͷţ�������������ڴ�ռ䣬��Ҫ�ⲿ�ͷš������ַ���������Ч�Ͱ�ȫ�������Ҫ������ֱ�Ӵ�������
		size_t size = *w * *h * 4;
		*pBuffer = new char[size];
		memcpy(*pBuffer, tempBuffer, size);

		FreeImage_Unload(dib);

		return 1;
	}

	int XResource::SaveTextureFile(const char* pFile, char* pBuffer, int w, int h)
	{
		FIBITMAP* dib = FreeImage_Allocate(w, h, 32);

		unsigned char* pPixel = FreeImage_GetBits(dib);

		memcpy(pPixel, pBuffer, w * h * 4);

		BOOL res = FreeImage_Save(FIF_PNG, dib, pFile, PNG_DEFAULT);

		FreeImage_Unload(dib);

		return res;
	}
}