﻿#include "PixelShader.h"

#include "../../../Graphics.h"

void Render::PixelShader::construct(ID3DBlob* shader_blob)
{
	context->device->CreatePixelShader(
		shader_blob->GetBufferPointer(),
		shader_blob->GetBufferSize(),
		nullptr,
		&_shader
	);
}

Render::PixelShader::PixelShader(Core::GraphicsContext* engine)
	: Shader(engine)
{
	_shader = nullptr;
}

Render::PixelShader::PixelShader(Core::GraphicsContext* engine, const wchar_t* path)
	: Shader(engine)
{
	read_file(path);
	release_blob();
}
