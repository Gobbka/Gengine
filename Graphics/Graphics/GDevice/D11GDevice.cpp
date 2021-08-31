#include "D11GDevice.h"
#include "../../Graphics.h"
#include "../../Render/d3d/Vertex.h"
#include "../../Render/d3d/Buffer/IndexBuffer.h"
#include "../../Render/d3d/Buffer/VertexBuffer.h"
#include "../../Render/Engine/Camera.h"

Render::D11GDevice::D11GDevice(ID3D11Device* device,Core::GraphicsContext* gfx)
{
	_device = device;
	_gfx = gfx;
}

Render::IIndexBuffer* Render::D11GDevice::alloc_index_buffer(unsigned size)
{
	return new IndexBuffer(_gfx, new UINT[size], size);
}

Render::IIndexBuffer* Render::D11GDevice::alloc_index_buffer(void* data, unsigned size)
{
	return new IndexBuffer(_gfx, (UINT*)data, size);
}

Render::IVertexBuffer* Render::D11GDevice::alloc_vertex_buffer(unsigned size, bool dynamic)
{
	return new VertexBuffer(_gfx, new Vertex[size], size, dynamic);
}

Render::IVertexBuffer* Render::D11GDevice::alloc_vertex_buffer(void* data, unsigned size, bool dynamic)
{
	return new VertexBuffer(_gfx, (Vertex*)data, size, dynamic);
}

Render::Texture* Render::D11GDevice::create_texture(Material& material)
{
	return new Texture(_gfx, material);
}

