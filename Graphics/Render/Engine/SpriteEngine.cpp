﻿#include "SpriteEngine.h"
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

void Render::SpriteEngine::bind_texture(Texture* texture)
{
	if(texture != _binded_texture)
	{
		texture->bind();
		_binded_texture = texture;
	}
}

void Render::SpriteEngine::begin_sprite_mode()
{
	if (_drawMode == DrawMode::sprite)
		return;

	if (_ps_active)
	{
		_graphicsContext->pixel_shader.bind(_texture_ps);
	}
	_texture_vs->bind();
	_graphicsContext->context->IASetInputLayout(_texture_layout);

	_drawMode = DrawMode::sprite;
}

void Render::SpriteEngine::begin_color_mode()
{
	if (_drawMode == DrawMode::color)
		return;

	if(_ps_active)
		_graphicsContext->pixel_shader.bind(_color_ps);
	_color_vs->bind();
	_graphicsContext->context->IASetInputLayout(_color_layout);

	_drawMode = DrawMode::color;
}

bool Render::SpriteEngine::set_ps_state(bool active)
{
	bool current_status = _ps_active;
	_ps_active = active;

	if (_ps_active)
	{
		switch (_drawMode)
		{
		case DrawMode::color:
			_graphicsContext->pixel_shader.bind(_color_ps);
		break;
		case DrawMode::sprite:
			_graphicsContext->pixel_shader.bind(_texture_ps);
		break;
		case DrawMode::none: break;
		}	
	}else
	{
		_graphicsContext->pixel_shader.remove();
	}
	
	return current_status;
}
