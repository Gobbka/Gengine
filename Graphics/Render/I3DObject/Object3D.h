#pragma once
#include "../d3d/Vertex.h"
#include "Types/Transform.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class IndexBuffer;
	class VertexBuffer;

	class __declspec(dllexport) Object3D
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
		virtual ~Object3D() = default;
		
		Object3D(Core::GraphicsContext*context,size_t vertex_size,IndexBuffer*index_buffer,Position3 pos = { 0,0,0 });
		Object3D(Core::GraphicsContext* context, VertexBuffer* buffer, IndexBuffer* index_buffer,Position3 pos = {0,0,0});
		
		virtual void draw();
	};
}
