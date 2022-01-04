#pragma once
#include "../IPass/IPass.h"
#include "../../Mesh.h"
#include "../../../Render/Common/Rasterizer.h"

namespace Render
{
	class DrawSkyboxPass final : public IPass
	{
		GEGraphics* _context;
		Mesh _skybox_cube;
		GERasterizer _skybox_rasterizer;
		void execute(Scene*) override;
	public:
		explicit DrawSkyboxPass(GEGraphics* context);
	};
}
