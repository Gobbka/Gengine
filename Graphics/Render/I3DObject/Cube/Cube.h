#pragma once
#include "../Mesh.h"
#include "Types/Types.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class Texture;
	struct DrawEvent;

	class __declspec(dllexport) Cube
	{
	public:
		static Mesh make(Core::GraphicsContext* context, Position3 pos, int size);
		static Mesh make_independent(Core::GraphicsContext* context, Position3 pos, int size);
	};
}
