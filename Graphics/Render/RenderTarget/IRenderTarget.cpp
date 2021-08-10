#include "IRenderTarget.h"

#include "../../Graphics.h"
#include "../d3d/Buffer/Texture.h"

Render::IRenderTarget::IRenderTarget(Core::GraphicsContext* context)
	: _texture(context)
{
	_targetView = nullptr;
	_context = context;
}

Render::IRenderTarget::IRenderTarget(Core::GraphicsContext* context, Texture texture)
	: _context(context),
	_texture(texture)
{
	assert(texture.is_render_target());
	assert(SUCCEEDED(context->device->CreateRenderTargetView(texture.texture(), nullptr, &_targetView)));
}

Render::IRenderTarget::IRenderTarget(Core::GraphicsContext* context, Surface texture_resolution)
	: _context(context),
	_texture(context, texture_resolution, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET)
{
	assert(SUCCEEDED(context->device->CreateRenderTargetView(_texture.texture(), nullptr, &_targetView)));
}

ID3D11Resource* Render::IRenderTarget::get_resource()
{
	return _texture.texture();
}

Render::Texture* Render::IRenderTarget::get_texture()
{
	return &_texture;
}

void Render::IRenderTarget::bind(ID3D11DepthStencilView* stencil) const
{
	_context->context->OMSetRenderTargets(1, &_targetView, stencil);
}

void Render::IRenderTarget::clear(Color3 color)
{
	auto float_color = Color4(color).to_float4();
	_context->context->ClearRenderTargetView(_targetView, (FLOAT*)&float_color);
}

void Render::IRenderTarget::release()
{
	if (_targetView)
		_targetView->Release();
}

