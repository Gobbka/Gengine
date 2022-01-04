#pragma once
#include "../../../Graphics/Mesh.h"
#include "Types/Types.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	struct DrawEvent;

	class __declspec(dllexport) Parallelepiped
	{
	public:
		static Mesh make(Core::GraphicsContext*context,Position3 pos, Vector3 resolution);
		static Mesh make_independent(Core::GraphicsContext* context, Position3 pos, Vector3 resolution);
	};
}
