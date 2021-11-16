#include "D11GDevice.h"

#include "../../Graphics.h"
#include "../../Render/d3d/Vertex.h"
#include "../../Render/d3d/Buffer/IndexBuffer.h"
#include "../../Render/d3d/Buffer/VertexBuffer.h"

D3D11_USAGE get_d11_usage(Render::IVertexBufferDesc::Usage usage)
{
	switch (usage)
	{
	case Render::IVertexBufferDesc::Usage::classic:
		return D3D11_USAGE_DEFAULT;
		break;
	case Render::IVertexBufferDesc::Usage::immutable:
		return D3D11_USAGE_IMMUTABLE;
	case Render::IVertexBufferDesc::Usage::dynamic:
		return D3D11_USAGE_DYNAMIC;
	}
}

Render::IVertexBuffer* Render::D11GDevice::alloc_vertex_buffer_impl(void* data, size_t element_size,
	IVertexBufferDesc desc)
{
	const D3D11_BUFFER_DESC vbuffer{
		element_size * desc.length,
		get_d11_usage(desc.usage),
		D3D11_BIND_VERTEX_BUFFER,
		(desc.usage == IVertexBufferDesc::Usage::dynamic ? D3D11_CPU_ACCESS_WRITE : 0u),
		0,
		sizeof(Vertex)
	};
	D3D11_SUBRESOURCE_DATA sd{ data,0,0 };

	ID3D11Buffer* buffer;

	assert(SUCCEEDED(_device->CreateBuffer(&vbuffer, &sd, &buffer)));

	return new VertexBuffer(_gfx, (Vertex*)data, desc.length, buffer);
}

Render::D11GDevice::D11GDevice(ID3D11Device* device,Core::GraphicsContext* gfx)
	: _device(device),
	_gfx(gfx)
{}

Render::IIndexBuffer* Render::D11GDevice::alloc_index_buffer(unsigned size)
{
	return new IndexBuffer(_gfx, new UINT[size], size);
}

Render::IIndexBuffer* Render::D11GDevice::alloc_index_buffer(void* data, unsigned size)
{
	return new IndexBuffer(_gfx, (UINT*)data, size);
}

Render::Texture* Render::D11GDevice::create_texture(ITexture2DDesc desc)
{
	return new Texture(_gfx, desc);
}

Render::Rasterizer Render::D11GDevice::create_rasterizer(RasterizerDesc desc)
{
	ID3D11RasterizerState* rs=nullptr;
	auto rsdesc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
	rsdesc.FrontCounterClockwise = desc.cull_mode_front;
	_device->CreateRasterizerState(&rsdesc, &rs);
	return { rs };
}

