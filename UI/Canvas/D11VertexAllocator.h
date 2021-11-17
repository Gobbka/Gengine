#pragma once
#include <Graphics/IBuffers/IVertexBuffer.h>
#include <Render/d3d/Vertex.h>

#include "Vertex2D.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	struct  __declspec(dllexport) GrowPolicy
	{
		UINT start_size;
		UINT step_size;
		UINT allocated;
		GrowPolicy(UINT start_size, UINT step_size)
		{
			this->start_size = start_size;
			this->step_size = step_size;
			this->allocated = 0;
		}
	};

	class __declspec(dllexport) D11VertexAllocator final
	{
	private:
		Core::GraphicsContext* _ctx;
		GrowPolicy _allocator;
		IVertexBuffer<UI::Vertex2D>* _vertex_buffer;

		IVertexBuffer<UI::Vertex2D>* alloc_vbuffer(UINT size) const;
		void set_vbuffer(IVertexBuffer<UI::Vertex2D>* buffer);
	public:
		UINT buffer_size() const;
		UINT last_index() const;

		Core::GraphicsContext* get_graphics_context() const;

		void update() const;

		void alloc(UINT size);

		UI::Vertex2D* get_ptr() const;

		void bind();

		D11VertexAllocator(Core::GraphicsContext* pEngine, IVertexBuffer<UI::Vertex2D>* buffer);
		explicit D11VertexAllocator(Core::GraphicsContext* pEngine);

		~D11VertexAllocator();
	};
}
