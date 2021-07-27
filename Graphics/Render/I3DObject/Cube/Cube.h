#pragma once
#include "../I3DObject.h"
#include "../Parallelepiped/Parallelepiped.h"
#include "Types/Types.h"

namespace Render
{
	class Texture;
	struct DrawEvent;

	class __declspec(dllexport) Cube : public Parallelepiped
	{
		Texture* texture;
	public:
		Cube(Position3 pos, Core::GraphicsContext* context);
	};
}
