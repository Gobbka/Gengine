#pragma once
#include "PrimitiveTopology.h"
#include "../Render/Common/GraphicsCommon.h"

namespace Render
{
	struct Vertex;

	struct __declspec(dllexport) Mesh final
	{
		GEVBuffer_Impl* buffer;
		GEIndexBuffer* index_buffer;
		PrimitiveTopology topology;
		
		Mesh(GEVBuffer_Impl* buffer, GEIndexBuffer* index_buffer);
	};
}
