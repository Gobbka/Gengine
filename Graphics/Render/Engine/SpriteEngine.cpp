#include "SpriteEngine.h"
#include "../d3d/Shader/PixelShader.h"
#include "../d3d/Shader/VertexShader.h"
#include "../../Graphics.h"

Render::SpriteEngine::SpriteEngine(Core::GraphicsContext* context,
	PixelShader* texture_ps, PixelShader* phong_ps, PixelShader* color_ps, VertexShader* texture_vs,
	ID3D11InputLayout* input_layout)
{
	_graphicsContext = context;
	_texture_ps = texture_ps;
	_texture_vs = texture_vs;
	_color_ps = color_ps;
	_phong_ps = phong_ps;
	_inputLayout = input_layout;
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
	
	if (_ps_active)
	{
		_graphicsContext->pixel_shader.bind(ps);
	}
	_texture_vs->bind();
	_graphicsContext->context->IASetInputLayout(_inputLayout);

	_current_ps = ps;
}

void Render::SpriteEngine::begin_color_mode()
{
	if(_ps_active)
		_graphicsContext->pixel_shader.bind(_color_ps);
	_texture_vs->bind();
	_graphicsContext->context->IASetInputLayout(_inputLayout);

	_current_ps = _color_ps;
}

bool Render::SpriteEngine::set_ps_state(bool active)
{
	bool current_status = _ps_active;
	_ps_active = active;

	if (_ps_active)
	{
		_graphicsContext->pixel_shader.bind(_current_ps);
	}else
	{
		_graphicsContext->pixel_shader.remove();
	}
	
	return current_status;
}
