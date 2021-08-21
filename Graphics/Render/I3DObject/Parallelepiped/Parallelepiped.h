#pragma once
#include "../Mesh.h"

namespace Render
{
	class Texture;
	struct DrawEvent;

	class __declspec(dllexport) Parallelepiped : public Mesh
	{
		Texture* texture;
	public:
		Parallelepiped(Position3 pos, Core::GraphicsContext* context,Vector3 resolution);

		void draw(DrawEvent3D event3d) override;
	};
}
