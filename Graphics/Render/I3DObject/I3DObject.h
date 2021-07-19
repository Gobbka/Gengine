#pragma once
#include "../d3d/Vertex.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class VertexBuffer;

	class I3DObject
	{
		VertexBuffer* _buffer;
	protected:
		// TODO: remove it from here
		Core::GraphicsContext* _context;
		
		void update_buffer();
		Vertex* vertices();

		void bind();
	public:
		
		I3DObject(Core::GraphicsContext*context,size_t vertex_size);
		
		virtual void draw() =0;
	};
}
