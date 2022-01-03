#pragma once
#include "../IPass/IPass.h"
#include "../../Mesh.h"
#include "../../../Render/Common/GraphicsCommon.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	class Scene;

	class DrawSkyboxPass final : public IPass
	{
		Core::GraphicsContext* _context;
		Mesh _skybox_cube;
		GERasterizer _skybox_rasterizer;
		void execute(Scene*) override;
	public:
		explicit DrawSkyboxPass(Core::GraphicsContext* context);
	};
}
