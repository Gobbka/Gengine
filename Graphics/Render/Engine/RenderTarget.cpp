#include "RenderTarget.h"

#include "../../Graphics.h"
#include "../d3d/Buffer/Texture.h"

Render::RenderTarget::RenderTarget(Core::GraphicsContext* context, IDXGISwapChain* swap)
	:  _context(context)
{
	ID3D11Resource* back_buffer;
	swap->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&back_buffer);

	context->device->CreateRenderTargetView(back_buffer, nullptr, &_targetView);

	back_buffer->Release();
}

Render::RenderTarget::RenderTarget(Core::GraphicsContext* context, Texture* texture)
	: _context(context)
{
	assert(SUCCEEDED(context->device->CreateRenderTargetView(texture->texture(), nullptr, &_targetView)));
}

void Render::RenderTarget::bind(ID3D11DepthStencilView* stencil) const
{
	_context->context->OMSetRenderTargets(1, &_targetView, stencil);
}

void Render::RenderTarget::clear(Color3 color)
{
	auto float_color = Color4(color).to_float4();
	_context->context->ClearRenderTargetView(_targetView, (FLOAT*)&float_color);
}
