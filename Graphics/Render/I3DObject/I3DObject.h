#pragma once
#include "../d3d/Vertex.h"
#include "Types/Transform.h"

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
		virtual ~I3DObject() = default;
		Core::Transform transform;
		
		I3DObject(Core::GraphicsContext*context,size_t vertex_size);
		I3DObject(Core::GraphicsContext*context,size_t vertex_size,Position3 pos);
		
		virtual void draw() =0;
	};
}
