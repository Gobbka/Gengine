#pragma once
#include "../../../Graphics/Mesh.h"
#include "Types/Types.h"

namespace Core {
	class DX11Graphics;
}

namespace Render
{
	struct DrawEvent;

	class __declspec(dllexport) Parallelepiped
	{
	public:
		static Mesh make(Core::DX11Graphics*context,Position3 pos, Vector3 resolution);
		static Mesh make_independent(Core::DX11Graphics* context, Position3 pos, Vector3 resolution);
	};
}
