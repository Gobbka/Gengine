#pragma once
#include "../I3DObject.h"
#include "Types/Types.h"

namespace Render
{
	class Texture;
	struct DrawEvent;

	class __declspec(dllexport) Cube : public I3DObject
	{
		Texture* texture;
	public:
		Cube(Position3 pos, Core::GraphicsContext* context);

		void set_texture(Render::Texture* texture);
		
		void draw() override;
	};
}
