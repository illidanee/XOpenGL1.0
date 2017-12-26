#pragma once

extern "C"
{
#include <libavutil/imgutils.h>
#include <libavutil/parseutils.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavutil/file.h>
}

namespace Smile
{
	class XVideo
	{
	public:
		static void Init();

	private:
		AVFormatContext* _pFC;
		AVCodecContext* _pCC;
		AVCodec* _pC;
		AVFrame* _pFrame;
		SwsContext* _pSC;

		int _VideoIndex;
		int _w;
		int _h;

		uint8_t *dst_data[4];
		int dst_linesize[4];
	
	public:
		int GetW() { return _w; }
		int GetH() { return _h; }

	public:
		XVideo();
		~XVideo();

		int LoadVideoFile(const char* pFile);
		int FreeVideoFile();
		void* ReadFrame();
	};
}