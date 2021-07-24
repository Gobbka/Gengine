#include "SpriteEngine.h"
#include "../d3d/Shader/PixelShader.h"
#include "../d3d/Shader/VertexShader.h"
#include "../../Graphics.h"

Render::SpriteEngine::SpriteEngine(Core::GraphicsContext* context, PixelShader* ps, VertexShader* vs, ID3D11InputLayout* layout)
{
	_texture_ps = ps;
	_texture_vs = vs;
	_layout = layout;
	
	_graphicsContext = context;
}

void Render::SpriteEngine::begin()
{
	auto* context = _graphicsContext->context();
	context->PSGetShader(&_old_ps, nullptr, 0);
	context->VSGetShader(&_old_vs, nullptr, 0);
	context->IAGetInputLayout(&_old_layout);
	
	
	_texture_ps->bind();
	_texture_vs->bind();

	_graphicsContext->context()->IASetInputLayout(_layout);
}

void Render::SpriteEngine::end()
{
	auto* context = _graphicsContext->context();
	context->PSSetShader(_old_ps, nullptr, 0);
	context->VSSetShader(_old_vs, nullptr, 0);
	context->IASetInputLayout(_old_layout);
}
