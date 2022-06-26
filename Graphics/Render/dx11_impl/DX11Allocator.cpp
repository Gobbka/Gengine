#include "DX11Allocator.h"

#include "BlendEngine.h"
#include "../../Graphics.h"
#include "../../Render/d3d/Vertex.h"
#include "../../Render/Common/IndexBuffer.h"
#include "Logger/Logger.h"

Render::DX11Allocator::DX11Allocator(ID3D11Device* device, GEGraphics* gfx)
	: _device(device)
	, _gfx(gfx)
{}

Render::GEIndexBuffer* Render::DX11Allocator::alloc_index_buffer(unsigned size)
{
	return new GEIndexBuffer(_gfx, new UINT[size], size);
}

Render::GEIndexBuffer* Render::DX11Allocator::alloc_index_buffer(void* data, unsigned size)
{
	return new GEIndexBuffer(_gfx, (UINT*)data, size);
}

Render::GETexture* Render::DX11Allocator::create_texture(ITexture2DDesc desc)
{
	return new GETexture(_gfx, desc);
}

Render::GERasterizer Render::DX11Allocator::create_rasterizer(RasterizerDesc desc)
{
	ID3D11RasterizerState* rs=nullptr;
	auto rsdesc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
	rsdesc.FrontCounterClockwise = desc.cull_mode_front;
	_device->CreateRasterizerState(&rsdesc, &rs);
	return { rs };
}
