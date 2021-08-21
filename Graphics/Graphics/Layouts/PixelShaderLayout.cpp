#include "PixelShaderLayout.h"


#include "../../Graphics.h"
#include "../../Render/d3d/Shader/PixelShader.h"

Render::PixelShaderLayout::PixelShaderLayout(Core::GraphicsContext* context)
{
	_context = context;
}

void Render::PixelShaderLayout::bind(PixelShader* shader)
{
	if(shader != _ps)
	{
		_context->context->PSSetShader(shader->get_d3d11_ps(), nullptr, 0);
		_ps = shader;
	}
}

void Render::PixelShaderLayout::remove()
{
	_context->context->PSSetShader(nullptr, nullptr, 0);
	_ps = nullptr;
}
