#pragma once
namespace Core {
	class GraphicsContext;
}

namespace Render {
	class IIndexBuffer;
	class IVertexBuffer;

	class IBufferAllocator
	{
	protected:
		Core::GraphicsContext* _context;
	public:
		IBufferAllocator(Core::GraphicsContext* context) : _context(context) {}

		virtual IVertexBuffer* alloc_vertex_buffer(unsigned size, bool dynamic = true)           =0;
		virtual IVertexBuffer* alloc_vertex_buffer(void*data,unsigned size, bool dynamic = true) =0;

		virtual IIndexBuffer* alloc_index_buffer(unsigned size) =0;
		virtual IIndexBuffer* alloc_index_buffer(void*data,unsigned size) =0;
	};
}
