#pragma once
#include "../IPass/IPass.h"
#include "../../Mesh.h"

namespace Render
{
	class GEPostEffect : public IPass
	{
		Mesh _screen_mesh;
	protected:
		GEGraphics* gfx;
		void do_effect();
	public:
		GEPostEffect(GEGraphics* context);
	};
}
