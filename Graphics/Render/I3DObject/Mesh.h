#pragma once
#include "../d3d/Vertex.h"
#include "Types/Transform.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	struct DrawEvent3D;
	class IndexBuffer;
	class VertexBuffer;

	class __declspec(dllexport) Mesh
	{
		VertexBuffer* _buffer;
		IndexBuffer* _index_buffer;
	protected:
		// TODO: remove it from here
		Core::GraphicsContext* _context;
		
		void update_buffer();
		Vertex* vertices();

		void bind();
	public:
		virtual ~Mesh() = default;
		
		Mesh(Core::GraphicsContext*context,size_t vertex_size,IndexBuffer*index_buffer,Position3 pos = { 0,0,0 });
		Mesh(Core::GraphicsContext* context, VertexBuffer* buffer, IndexBuffer* index_buffer,Position3 pos = {0,0,0});
		
		virtual void draw(DrawEvent3D event3d);
	};
}
