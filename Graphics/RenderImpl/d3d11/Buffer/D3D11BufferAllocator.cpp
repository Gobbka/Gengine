#include "D3D11BufferAllocator.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "../Vertex.h"

Render::IIndexBuffer* Render::D3D11BufferAllocator::alloc_index_buffer(unsigned size)
{
	return new IndexBuffer(_context, new UINT[size], size);
}

Render::IIndexBuffer* Render::D3D11BufferAllocator::alloc_index_buffer(void* data, unsigned size)
{
	return new IndexBuffer(_context, (UINT*)data, size);
}

Render::IVertexBuffer* Render::D3D11BufferAllocator::alloc_vertex_buffer(unsigned size, bool dynamic)
{
	return new VertexBuffer(_context, new Vertex[size], size, dynamic);
}

Render::IVertexBuffer* Render::D3D11BufferAllocator::alloc_vertex_buffer(void* data, unsigned size, bool dynamic)
{
	return new VertexBuffer(_context, (Vertex*)data, size, dynamic);
}
