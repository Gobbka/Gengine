#pragma once
#include "Types/Types.h"
#include "../../../Render/Common/GraphicsCommon.h"

namespace Render
{
	struct Mesh;
	struct DrawEvent;

	class __declspec(dllexport) Cube
	{
	public:
		static Mesh make(GEGraphics* context, Position3 pos, int size);
		static Mesh make_independent(GEGraphics* context, Position3 pos, int size);
	};
}
