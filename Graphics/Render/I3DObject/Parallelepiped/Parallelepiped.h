#pragma once
#include "../Object3D.h"

namespace Render
{
	class Texture;
	struct DrawEvent;

	class __declspec(dllexport) Parallelepiped : public Object3D
	{
		Texture* texture;
	public:
		Parallelepiped(Position3 pos, Core::GraphicsContext* context,Vector3 resolution);

		void set_texture(Render::Texture* texture);

		void draw() override;
	};
}
