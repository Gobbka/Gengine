#pragma once
#include "../../../Graphics/Mesh.h"
#include "Types/Types.h"

namespace Render
{
	struct DrawEvent;

	class __declspec(dllexport) Parallelepiped
	{
	public:
		static Mesh make(GEGraphics*context,Position3 pos, Vector3 resolution);
		static Mesh make_independent(GEGraphics* context, Position3 pos, Vector3 resolution);
	};
}
