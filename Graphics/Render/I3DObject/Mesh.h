#pragma once
#include "../d3d/Vertex.h"
#include "Types/Transform.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class IIndexBuffer;
	class IVertexBuffer;
	struct DrawEvent3D;

	class __declspec(dllexport) Mesh final
	{
		IVertexBuffer* _buffer;
		IIndexBuffer* _index_buffer;

		void bind();
	public:
		
		Mesh(IVertexBuffer* buffer, IIndexBuffer* index_buffer);
		
		void draw(DrawEvent3D event3d);
	};
}
