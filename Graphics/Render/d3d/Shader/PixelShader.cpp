#include "PixelShader.h"
#include <d3dcompiler.h>
#include "../../../Graphics.h"
#include "Logger/Logger.h"

void Render::PixelShader::construct(ID3DBlob* shader_blob)
{
	context->device->CreatePixelShader(
		shader_blob->GetBufferPointer(),
		shader_blob->GetBufferSize(),
		nullptr,
		&_shader
	);
}

Render::PixelShader::PixelShader(GEGraphics* engine, const wchar_t* path)
	: IShader(engine)
	, _shader(nullptr)
{
	ID3DBlob* blob = nullptr;
	D3DReadFileToBlob(path, &blob);

	GEAssert(blob != nullptr).abort(TEXT("Cannot read file to shader blob"));

	construct(blob);
	blob->Release();
}
