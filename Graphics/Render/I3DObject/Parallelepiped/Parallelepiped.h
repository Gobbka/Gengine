#pragma once
#include "../I3DObject.h"

namespace Render
{
	class Texture;
	struct DrawEvent;

	class __declspec(dllexport) Parallelepiped : public I3DObject
	{
		Texture* texture;
	public:
		Parallelepiped(Position3 pos, Core::GraphicsContext* context,Vector3 resolution);

		void set_texture(Render::Texture* texture);

		void draw() override;
	};
}
