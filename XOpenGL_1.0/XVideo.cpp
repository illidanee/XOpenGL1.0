#include "XVideo.h"

extern "C"
{
#include<libavformat/avformat.h>
}


namespace Smile
{
	void XVideo::Init()
	{
		av_register_all();
	}

	XVideo::XVideo()
	{
		_pFC = NULL;
		_pCC = NULL;
		_pC = NULL;
		_pFrame = NULL;
		_pSC = NULL;

		_VideoIndex = -1;
		_w = -1;
		_h = -1;
	}

	XVideo::~XVideo()
	{

	}

	int XVideo::LoadVideoFile(const char* pFile)
	{
		//_pFC = avformat_alloc_context();
		int res = avformat_open_input(&_pFC, pFile, NULL, NULL);
		if (res != 0)
		{
			//���ļ�����
			return 0;
		}

		res = avformat_find_stream_info(_pFC, NULL);
		if (res < 0)
		{
			//�ļ�û����Ƶ��
			return -1;
		}

		_VideoIndex = -1;
		for (unsigned int i = 0; i < _pFC->nb_streams; ++i)
		{
			_pCC = _pFC->streams[i]->codec;
			if (_pCC->codec_type == AVMEDIA_TYPE_VIDEO)
			{
				_VideoIndex = i;
				break;
			}
		}
		if (_VideoIndex == -1)
		{
			//�ļ�û����Ƶ��
			return -2;
		}
			
		_pC = avcodec_find_decoder(_pCC->codec_id);
		if (!_pC)
		{
			//û���ҵ�������
			return -3;
		}

		res = avcodec_open2(_pCC, _pC, NULL);
		if (res != 0)
		{
			//�򿪽���������
			return -4;
		}

		_pFrame = av_frame_alloc();

		_w = _pCC->width;
		_h = _pCC->height;

		_pSC = sws_getContext(_w, _h, _pCC->pix_fmt, _w, _h, AV_PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);

		if ((res = av_image_alloc(dst_data, dst_linesize, _w, _h, AV_PIX_FMT_RGB24, 1)) < 0)
		{
			//---
			return  -5;
		}

		return 1;
	}

	int XVideo::FreeVideoFile()
	{
		sws_freeContext(_pSC);
		av_free(_pFrame);
		avcodec_close(_pCC);
		avformat_close_input(&_pFC);	

		_pFC = NULL;
		_pCC = NULL;
		_pC = NULL;
		_pFrame = NULL;
		_pSC = NULL;

		_VideoIndex = -1;
		_w = -1;
		_h = -1;

		return 1;
	}

	void* XVideo::ReadFrame()
	{
		AVPacket packet;
		av_init_packet(&packet);
		while (1)
		{
			if (av_read_frame(_pFC, &packet))
			{
				av_free_packet(&packet);
				return NULL;
			}

			if (packet.stream_index != _VideoIndex)
			{
				continue;
			}

			int finish = 0;
			int res = avcodec_decode_video2(_pCC, _pFrame, &finish, &packet);
			if (finish)
			{
				int res = sws_scale(_pSC, (const uint8_t* const*)_pFrame->data, _pFrame->linesize, 0, _pCC->height, dst_data, dst_linesize);
				av_free_packet(&packet);

				return  dst_data[0];
			}
		}
	}
}