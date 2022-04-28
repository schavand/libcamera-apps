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
	
	libcameraAppHandle createLibcameraApp()
	{

		return new LibcameraApp;
	}

	void freeLibcameraApp(libcameraAppHandle h)
	{
		delete (LibcameraApp *) h;
	}

	void OpenCamera(libcameraAppHandle h)
	{
		((LibcameraApp *)h)->OpenCamera();
	}

	void CloseCamera(libcameraAppHandle h)
	{
		((LibcameraApp *)h)->CloseCamera();
	}

	void ConfigureViewfinder(libcameraAppHandle h)
	{
		((LibcameraApp *)h)->ConfigureViewfinder();
	}
	
	void ConfigureStill(libcameraAppHandle h, unsigned int flags)
	{
		((LibcameraApp *)h)->ConfigureStill(flags);
	}

	void ConfigureVideo(libcameraAppHandle h, unsigned int flags)
	{
		((LibcameraApp *)h)->ConfigureVideo(flags);
	}

	void Teardown(libcameraAppHandle h)
	{
		((LibcameraApp *)h)->Teardown();
	}

	void StartCamera(libcameraAppHandle h)
	{
		((LibcameraApp *)h)->StartCamera();
	}
	void StopCamera(libcameraAppHandle h)
	{
		((LibcameraApp *)h)->StopCamera();
	}

	void Wait(libcameraAppHandle h, libcameraAppMsg m)
	{
		*((LibcameraApp::Msg *)m) = ((LibcameraApp *)h)->Wait();
	}

	libcameraAppMsg createLibcameraAppMsg()
	{
		void *m = malloc(sizeof(LibcameraApp::Msg));
		return m;
	}

	void freeLibcameraAppMsg(libcameraAppMsg m)
	{
		free(m);
	}

	int getLibcameraMessageType(libcameraAppMsg m)
	{
		return  static_cast<int>(((LibcameraApp::Msg *)m)->type);
	}

	void *getLibcameraMessagePayload(libcameraAppMsg m)
	{
		return  static_cast<void*>(&((LibcameraApp::Msg *)m)->payload);
	}

	void ShowPreview(libcameraAppHandle h, void* completed_request, void *stream)
	{
		CompletedRequestPtr *c = static_cast<CompletedRequestPtr *>(completed_request);
		((LibcameraApp *) h)->ShowPreview(*c, static_cast<libcamera::Stream *>(stream));
	}

	void *getCompletedRequestPtr(libcameraAppMsg m)
	{
		return static_cast<void*>(&std::get<CompletedRequestPtr>(((LibcameraApp::Msg *)m)->payload));
	}
}
