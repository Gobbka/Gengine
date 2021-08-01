#pragma once
#include "../../../BufferAllocator.h"

namespace Render
{
	class D3D11BufferAllocator : public Render::IBufferAllocator
	{
	public:
		D3D11BufferAllocator(Core::GraphicsContext* context) : IBufferAllocator(context) {}

		IIndexBuffer* alloc_index_buffer(unsigned size) override;
		IIndexBuffer* alloc_index_buffer(void* data, unsigned size) override;

		IVertexBuffer* alloc_vertex_buffer(unsigned size, bool dynamic) override;
		IVertexBuffer* alloc_vertex_buffer(void* data, unsigned size, bool dynamic) override;
	};
}