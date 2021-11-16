#pragma once
#include "PrimitiveTopology.h"

namespace Render
{
	struct Vertex;
	class IIndexBuffer;
	template<typename T>
	class IVertexBuffer;

	struct __declspec(dllexport) Mesh final
	{
		IVertexBuffer<Vertex>* buffer;
		IIndexBuffer* index_buffer;
		PrimitiveTopology topology;
		
		Mesh(IVertexBuffer<Vertex>* buffer, IIndexBuffer* index_buffer);
	};
}
