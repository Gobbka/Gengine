#include "PixelShader.h"
#include "../../Engine/Camera.h"

void Render::PixelShader::construct(ID3DBlob* shader_blob)
{
	_engine->device()->CreatePixelShader(
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

void Render::PixelShader::bind()
{
	_engine->context()->PSSetShader(_shader, nullptr, 0);
}
