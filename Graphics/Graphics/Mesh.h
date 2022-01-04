#pragma once
#include "../Render/Engine/PrimitiveTopology.h"
#include "../Render/Common/GraphicsCommon.h"

namespace Render
{
	struct Vertex;
	template<typename T>
	class IVertexBuffer;

	struct __declspec(dllexport) Mesh final
	{
		IVertexBuffer<Vertex>* buffer;
		GEIndexBuffer* index_buffer;
		PrimitiveTopology topology;
		
		Mesh(IVertexBuffer<Vertex>* buffer, GEIndexBuffer* index_buffer);
	};
}
