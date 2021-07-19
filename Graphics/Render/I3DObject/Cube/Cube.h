#pragma once
#include "../I3DObject.h"

namespace Render
{
	struct DrawEvent;

	class Cube : public I3DObject
	{
	public:
		Cube(Core::GraphicsContext* context);

		
		void draw() override;
	};
}
