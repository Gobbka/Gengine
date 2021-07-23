#pragma once
#include <Windows.h>

#include "../Render/d3d/Vertex.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class Camera;
	class VertexBuffer;

	class __declspec(dllexport) D3D11Canvas
	{
	private:
		struct  __declspec(dllexport) Allocator
		{
			UINT start_size;
			UINT step_size;
			UINT allocated;
			Allocator(UINT start_size, UINT step_size)
			{
				this->start_size = start_size;
				this->step_size = step_size;
				this->allocated = 0;
			}
		};
	private:
		Core::GraphicsContext* _engine;
		Allocator _allocator;

		VertexBuffer* alloc_vbuffer(UINT size) const;
		void set_vbuffer(::Render::VertexBuffer* buffer);

		VertexBuffer* _vertex_buffer;

	public:
		UINT buffer_size() const;
		UINT get_allocated_size() const;

		Core::GraphicsContext* get_graphics_context() const;

		virtual void update() const;

		void alloc_vertexes(UINT size);

	public:
		Vertex* get_ptr() const;
		VertexBuffer* get_vbuffer() const;

		void bind();

		D3D11Canvas(Core::GraphicsContext* pEngine, VertexBuffer* buffer);
		explicit D3D11Canvas(Core::GraphicsContext* pEngine);

		virtual ~D3D11Canvas();
	};
}
