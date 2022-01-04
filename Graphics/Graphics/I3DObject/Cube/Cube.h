#pragma once
#include "Types/Types.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	struct Mesh;
	struct DrawEvent;

	class __declspec(dllexport) Cube
	{
	public:
		static Mesh make(Core::GraphicsContext* context, Position3 pos, int size);
		static Mesh make_independent(Core::GraphicsContext* context, Position3 pos, int size);
	};
}
