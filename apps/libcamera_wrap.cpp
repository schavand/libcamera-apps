/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2021, Raspberry Pi (Trading) Ltd.
 *
 * libcamera_wrap.cpp - wrap C library
 */

//


#include "libcamera_wrap.h"
#include "core/libcamera_app.hpp"
#include "core/still_options.hpp"


extern "C" {
	
	libcameraAppHandle *createLibcameraApp()
	{

		return reinterpret_cast<libcameraAppHandle*>(new LibcameraApp());
	}

	void freeLibcameraApp(libcameraAppHandle *h)
	{
		delete reinterpret_cast<LibcameraApp*>(h);
	}

	void OpenCamera(libcameraAppHandle *h)
	{
		reinterpret_cast<LibcameraApp*>(h)->OpenCamera();
	}

	libcameraOptions *GetOptions(libcameraAppHandle *h)
	{
		return reinterpret_cast<libcameraOptions*>(reinterpret_cast<LibcameraApp*>(h)->GetOptions());
	}

	bool ParseOptions(libcameraOptions *o, int argc, char *argv[])
	{
		return reinterpret_cast<Options *>(o)->Parse(argc, argv);
	}

	void CloseCamera(libcameraAppHandle *h)
	{
		((LibcameraApp *)h)->CloseCamera();
	}

	void ConfigureViewfinder(libcameraAppHandle *h)
	{
		((LibcameraApp *)h)->ConfigureViewfinder();
	}
	
	void ConfigureStill(libcameraAppHandle *h, unsigned int flags)
	{
		((LibcameraApp *)h)->ConfigureStill(flags);
	}

	void ConfigureVideo(libcameraAppHandle *h, unsigned int flags)
	{
		((LibcameraApp *)h)->ConfigureVideo(flags);
	}

	void Teardown(libcameraAppHandle *h)
	{
		((LibcameraApp *)h)->Teardown();
	}

	void StartCamera(libcameraAppHandle *h)
	{
		((LibcameraApp *)h)->StartCamera();
	}
	void StopCamera(libcameraAppHandle *h)
	{
		((LibcameraApp *)h)->StopCamera();
	}

/*	libcameraAppMsg *libcameraWait(libcameraAppHandle *h)
	{
		static LibcameraApp::Msg msg = ((LibcameraApp *)h)->Wait();
		return reinterpret_cast<libcameraAppMsg*>(&msg);
	}
*/
	void libcameraWait(libcameraAppHandle *h, libcameraAppMsg *m)
	{
		*reinterpret_cast<LibcameraApp::Msg*>(m) = ((LibcameraApp *)h)->Wait();
	}

	int getLibcameraMessageType(libcameraAppMsg *m)
	{
		return  static_cast<int>(((LibcameraApp::Msg *)m)->type);
	}

	void *getLibcameraMessagePayload(libcameraAppMsg *m)
	{
		return  static_cast<void*>(&((LibcameraApp::Msg *)m)->payload);
	}

	void ShowPreview(libcameraAppHandle *h, libcameraCompletedRequestPtr* completed_request, libcameraStream *stream)
	{
		((LibcameraApp *) h)->ShowPreview(*reinterpret_cast<CompletedRequestPtr *>(completed_request), reinterpret_cast<libcamera::Stream *>(stream));
	}

	libcameraCompletedRequestPtr *getCompletedRequestPtr(libcameraAppMsg *m)
	{
		return reinterpret_cast<libcameraCompletedRequestPtr*>(&(((LibcameraApp::Msg *)m)->payload));
//		return reinterpret_cast<libcameraCompletedRequestPtr*>(&std::get<CompletedRequestPtr>(((LibcameraApp::Msg *)m)->payload));
	}

	libcameraStream *getViewfinderStream(libcameraAppHandle *h, libcameraStreamInfo *info)
	{
		return (libcameraStream *)(reinterpret_cast<LibcameraApp*>(h)->ViewfinderStream(reinterpret_cast<StreamInfo *>(info)));
	}
	
	libcameraStream *getStillStream(libcameraAppHandle *h, libcameraStreamInfo *info)
	{
		return (libcameraStream *)(reinterpret_cast<LibcameraApp *>(h)->StillStream(reinterpret_cast<StreamInfo *>(info)));
	}
	
	libcameraStream *getRawStream(libcameraAppHandle *h, libcameraStreamInfo *info)
	{
		return (libcameraStream *)(reinterpret_cast<LibcameraApp *>(h)->RawStream(reinterpret_cast<StreamInfo *>(info)));
	}

	libcameraStream *getVideoStream(libcameraAppHandle *h, libcameraStreamInfo *info)
	{
		return (libcameraStream *)(reinterpret_cast<LibcameraApp *>(h)->VideoStream(reinterpret_cast<StreamInfo *>(info)));
	}
	
	libcameraStream *LoresStream(libcameraAppHandle *h, libcameraStreamInfo *info)
	{
		return (libcameraStream *)(reinterpret_cast<LibcameraApp *>(h)->LoresStream(reinterpret_cast<StreamInfo *>(info)));
	}

    libcameraStreamInfo *createStreamInfo()
	{
		return reinterpret_cast<libcameraStreamInfo *>(new StreamInfo());
	}

    uint32_t getStreamInfoWidth(libcameraStreamInfo *info)
	{
		return reinterpret_cast<StreamInfo*>(info)->width;
	}

    uint32_t getStreamInfoHeight(libcameraStreamInfo *info)
	{
		return reinterpret_cast<StreamInfo*>(info)->height;
	}    

    uint32_t getStreamInfoStride(libcameraStreamInfo *info)
	{
		return reinterpret_cast<StreamInfo*>(info)->stride;
	}    

    uint32_t getStreamInfoPixel(libcameraStreamInfo *info)
	{
		return reinterpret_cast<StreamInfo*>(info)->pixel_format.fourcc();
	}    

    libcameraAppMsg *createAppMsg()
	{
		return reinterpret_cast<libcameraAppMsg *>(new LibcameraApp::Msg({}));
	}

	uint8_t *getFrame(libcameraAppHandle *h, libcameraAppMsg *msg, libcameraStream *s)
	{ 
//		const std::vector<libcamera::Span<uint8_t>> mem = app.Mmap((*reinterpret_cast<CompletedRequestPtr*>(payload))->buffers[stream])
		CompletedRequestPtr &_payload = std::get<CompletedRequestPtr>(reinterpret_cast<LibcameraApp::Msg *>(msg)->payload);
		const std::vector<libcamera::Span<uint8_t>> mem = reinterpret_cast<LibcameraApp *>(h)->Mmap(_payload->buffers[reinterpret_cast<libcamera::Stream*>(s)]);
		return (uint8_t *)(mem[0].data());
	}


	void optionSetValue(libcameraOptions *o, OptionList ol, void *value)
	{
		switch (ol)
		{
			case awb_gain_r:
				reinterpret_cast<Options*>(o)->awb_gain_r = *(float *)value;
				break;
			case awb_gain_b:
				reinterpret_cast<Options*>(o)->awb_gain_b = *(float *)value;
				break;
		}
	}

    void freeStreamInfo(libcameraStreamInfo *s)
	{
		delete reinterpret_cast<StreamInfo*>(s);
	}
}
