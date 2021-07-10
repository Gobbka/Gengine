#include "PixelShader.h"
#include "../../Engine/D3DEngine.h"

void Render::PixelShader::construct(ID3DBlob* shader_blob)
{
	_engine->device()->CreatePixelShader(
		shader_blob->GetBufferPointer(),
		shader_blob->GetBufferSize(),
		nullptr,
		&_shader
	);
}

Render::PixelShader::PixelShader(D3DEngine* engine)
	: Shader(engine)
{
	_shader = nullptr;
}

void Render::PixelShader::bind()
{
	_engine->context()->PSSetShader(_shader, nullptr, 0);
}
