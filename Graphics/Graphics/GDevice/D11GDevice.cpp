#include "D11GDevice.h"

#include "../../Graphics.h"
#include "../../Render/d3d/Vertex.h"
#include "../../Render/d3d/Buffer/IndexBuffer.h"
#include "../../Render/d3d/Buffer/VertexBuffer.h"

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

Render::IVertexBuffer* Render::D11GDevice::alloc_vertex_buffer(void* data, IVertexBufferDesc desc)
{
	return new VertexBuffer(_gfx, new Vertex[desc.size], desc);
}

Render::IVertexBuffer* Render::D11GDevice::alloc_vertex_buffer(unsigned size, bool dynamic)
{
	IVertexBufferDesc buffer_desc;
	buffer_desc.size = size;
	buffer_desc.usage = dynamic ? IVertexBufferDesc::Usage::dynamic : IVertexBufferDesc::Usage::classic;
	return new VertexBuffer(_gfx, new Vertex[size], buffer_desc);
}

Render::IVertexBuffer* Render::D11GDevice::alloc_vertex_buffer(void* data, unsigned size, bool dynamic)
{
	IVertexBufferDesc buffer_desc;
	buffer_desc.size = size;
	buffer_desc.usage = dynamic ? IVertexBufferDesc::Usage::dynamic : IVertexBufferDesc::Usage::classic;

	return new VertexBuffer(_gfx, (Vertex*)data, buffer_desc);
}

Render::Texture* Render::D11GDevice::create_texture(ITexture2DDesc desc)
{
	return new Texture(_gfx, desc);
}

