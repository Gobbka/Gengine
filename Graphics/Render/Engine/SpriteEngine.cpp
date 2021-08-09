#include "SpriteEngine.h"
#include "../d3d/Shader/PixelShader.h"
#include "../d3d/Shader/VertexShader.h"
#include "../../Graphics.h"

Render::SpriteEngine::SpriteEngine(Core::GraphicsContext* context, PixelShader* texture_ps, VertexShader* texture_vs,
	ID3D11InputLayout* texture_layout, PixelShader* color_ps, VertexShader* color_vs, ID3D11InputLayout* color_layout)
{
	_graphicsContext = context;
	_texture_ps = texture_ps;
	_texture_vs = texture_vs;
	_color_ps = color_ps;
	_color_vs = color_vs;
	_texture_layout = texture_layout;
	_color_layout = color_layout;
}

void Render::SpriteEngine::begin_sprite_mode()
{
	if (_drawMode == DrawMode::sprite)
		return;
	
	_texture_ps->bind();
	_texture_vs->bind();
	_graphicsContext->context->IASetInputLayout(_texture_layout);

	_drawMode = DrawMode::sprite;
}

void Render::SpriteEngine::begin_color_mode()
{
	if (_drawMode == DrawMode::color)
		return;
	
	_color_ps->bind();
	_color_vs->bind();
	_graphicsContext->context->IASetInputLayout(_color_layout);

	_drawMode = DrawMode::color;
}

void Render::SpriteEngine::end()
{
	//_drawMode = DrawMode::none;
}
