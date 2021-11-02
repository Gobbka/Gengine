#include "PixelShader.h"

#include <d3dcompiler.h>

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

Render::PixelShader::PixelShader(Core::GraphicsContext* engine, const wchar_t* path)
	: IShader(engine)
{
	ID3DBlob* blob;
	D3DReadFileToBlob(path, &blob);
	if(blob)
	{
		construct(blob);
		blob->Release();
	}
}
