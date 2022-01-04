#pragma once
#include "Types/Types.h"

namespace Core {
	class DX11Graphics;
}

namespace Render
{
	struct Mesh;
	struct DrawEvent;

	class __declspec(dllexport) Cube
	{
	public:
		static Mesh make(Core::DX11Graphics* context, Position3 pos, int size);
		static Mesh make_independent(Core::DX11Graphics* context, Position3 pos, int size);
	};
}
