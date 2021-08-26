#pragma once
#include "../Mesh.h"

namespace Render
{
	class Texture;
	struct DrawEvent;

	class __declspec(dllexport) Parallelepiped
	{
	public:
		static Mesh make(Core::GraphicsContext*context,Position3 pos, Vector3 resolution);
	};
}
