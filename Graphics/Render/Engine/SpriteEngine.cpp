#include "SpriteEngine.h"

#include "../d3d/Shader/PixelShader.h"
#include "../d3d/Shader/VertexShader.h"
#include "../../Graphics.h"
#include "../../IGContext.h"

Render::SpriteEngine::SpriteEngine(Core::GraphicsContext* context,
                                   PixelShader* texture_ps, PixelShader* phong_ps, PixelShader* color_ps, VertexShader* texture_vs)
{
	_binded_texture = nullptr;
	_graphicsContext = context;
	_texture_ps = texture_ps;
	_texture_vs = texture_vs;
	_color_ps = color_ps;
	_phong_ps = phong_ps;
}

void Render::SpriteEngine::bind_texture(Texture* texture)
{
	if(texture != _binded_texture)
	{
		texture->bind();
		_binded_texture = texture;
	}
}

void Render::SpriteEngine::begin_sprite_mode(bool light)
{
	auto* ps = light ? _phong_ps : _texture_ps;

	_graphicsContext->get_context()->set_pixel_shader(ps);
	_texture_vs->bind();
}

void Render::SpriteEngine::begin_color_mode()
{
	_graphicsContext->get_context()->set_pixel_shader(_color_ps);
	_texture_vs->bind();
}
