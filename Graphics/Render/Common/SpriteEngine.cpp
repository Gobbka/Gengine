#include "SpriteEngine.h"
#include "../../Graphics.h"
#include "../Common/IGContext.h"

Render::SpriteEngine::SpriteEngine(GEGraphics* context)
	: _graphicsContext(context)
	, _context(context->get_context())
{}

void Render::SpriteEngine::bind_texture(GETexture* texture,unsigned slot)
{
	if(texture != _binded_texture[slot])
	{
		_context->set_shader_resource(texture, slot);
		_binded_texture[slot] = texture;
	}
}

void Render::SpriteEngine::begin_sprite_mode(bool light)
{
	auto* ps = light ? 
		_graphicsContext->shader_collection.get<PixelShader>(L"d3d11\\phong_ps.cso") :
		_graphicsContext->shader_collection.get<PixelShader>(L"d3d11\\texture_ps.cso");

	_graphicsContext->get_context()->set_pixel_shader(ps);
}

void Render::SpriteEngine::begin_color_mode()
{
	_graphicsContext->get_context()
		->set_pixel_shader(_graphicsContext->shader_collection.get<PixelShader>(L"d3d11\\pixel_shader.cso"));
}
