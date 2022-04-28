/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2021, Raspberry Pi (Trading) Limited
 *
 * negate_stage.cpp - image negate effect
 */

#include <libcamera/stream.h>

#include "core/libcamera_app.hpp"

#include "post_processing_stages/post_processing_stage.hpp"

using Stream = libcamera::Stream;

class NegateStage : public PostProcessingStage
{
public:
	NegateStage(LibcameraApp *app) : PostProcessingStage(app) {}

	char const *Name() const override;

	void Read(boost::property_tree::ptree const &params) override {}

	void Configure() override;

	bool Process(CompletedRequestPtr &completed_request) override;

private:
	Stream *stream_;
	uint32_t taille=0;
	uint8_t *ptrm,*ptrp;

};

#define NAME "negate"

char const *NegateStage::Name() const
{
	return NAME;
}

void NegateStage::Configure()
{
	stream_ = app_->GetMainStream();
}

bool NegateStage::Process(CompletedRequestPtr &completed_request)
{
	libcamera::Span<uint8_t> buffer = app_->Mmap(completed_request->buffers[stream_])[0];
	uint8_t *ptr = (uint8_t *)buffer.data();
//	uint32_t taille=4L*buffer.size()/6;
//	uint8_t *ptrm=ptr+taille,*ptrp=ptr+5L*taille/4;
//	uint8_t a;
	
	// Constraints on the stride mean we always have multiple-of-4 bytes.
	for (unsigned int i = 0; i < 480; i++)
	{
		for (unsigned int j = 0; j <640; j++)
		{
			if ((j==320)||(i==240))
				*ptr ^= 0xFF;
			ptr++;
		};
	};
	return false;
}

static PostProcessingStage *Create(LibcameraApp *app)
{
	return new NegateStage(app);
}

static RegisterStage reg(NAME, &Create);
