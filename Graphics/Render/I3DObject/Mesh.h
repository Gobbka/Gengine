#pragma once
#include "../../Graphics/PrimitiveTopology.h"

namespace Render
{
	class IIndexBuffer;
	class IVertexBuffer;

	struct __declspec(dllexport) Mesh final
	{
		IVertexBuffer* buffer;
		IIndexBuffer* index_buffer;
		PrimitiveTopology topology;
		
		Mesh(IVertexBuffer* buffer, IIndexBuffer* index_buffer);
	};
}
