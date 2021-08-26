#include "RenderTarget.h"

#include "../../Graphics.h"
#include "../d3d/Buffer/Texture.h"

Render::RenderTarget::RenderTarget(Core::GraphicsContext* context, IDXGISwapChain* swap)
	:  _context(context),
	_texture(context)
{
	ID3D11Resource* back_buffer;
	swap->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&back_buffer);

	D3D11_TEXTURE2D_DESC desc;
	((ID3D11Texture2D*)back_buffer)->GetDesc(&desc);
	
	assert(SUCCEEDED(context->device->CreateRenderTargetView(back_buffer, nullptr, &_targetView)));
	_texture = Texture(context, (ID3D11Texture2D*)back_buffer);
	
	back_buffer->Release();
}

Render::RenderTarget::RenderTarget(Core::GraphicsContext* context, Texture texture)
	: _context(context),
	_texture(texture)
{
	assert(texture.is_render_target());	
	assert(SUCCEEDED(context->device->CreateRenderTargetView(texture.texture(), nullptr, &_targetView)));
}

Render::RenderTarget::RenderTarget(Core::GraphicsContext* context, Surface texture_resolution)
	: _context(context),
	_texture(context, texture_resolution, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET)
{
	assert(SUCCEEDED(context->device->CreateRenderTargetView(_texture.texture(), nullptr, &_targetView)));
}

Render::RenderTarget::RenderTarget(Core::GraphicsContext* context, RenderTargetUsage usage)
	: _context(context),
	_texture(context)
{
	if(usage == RenderTargetUsage::null)
	{
		_targetView = nullptr;
	}
}

ID3D11Resource* Render::RenderTarget::get_resource()
{
	return _texture.texture();
}

Render::Texture* Render::RenderTarget::get_texture()
{
	return &_texture;
}

void Render::RenderTarget::bind(ID3D11DepthStencilView* stencil) const
{
	auto num = _targetView == nullptr ? 0 : 1;
	_context->context->OMSetRenderTargets(num, _targetView == nullptr ? nullptr : &_targetView, stencil);
}

void Render::RenderTarget::clear(Color4 color)
{
	auto float_color = color.to_float4();

	if (_targetView != nullptr)
		_context->context->ClearRenderTargetView(_targetView, (FLOAT*)&float_color);
}

void Render::RenderTarget::clear(Color3 color)
{
	auto float_color = Color4(color).to_float4();
	
	if(_targetView != nullptr)
		_context->context->ClearRenderTargetView(_targetView, (FLOAT*)&float_color);
}

void Render::RenderTarget::clear()
{
	clear(clear_color);
}

void Render::RenderTarget::release()
{
	if(_targetView)
		_targetView->Release();
}
