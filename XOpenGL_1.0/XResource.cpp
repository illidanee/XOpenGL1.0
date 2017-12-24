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

		*pBuffer = (char*)FreeImage_GetBits(dib);
		*w = FreeImage_GetWidth(dib);
		*h = FreeImage_GetHeight(dib);
		FreeImage_Unload(dib);

		return 1;
	}
}