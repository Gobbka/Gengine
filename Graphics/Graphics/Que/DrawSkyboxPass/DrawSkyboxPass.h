#pragma once
#include "../IPass/IPass.h"
#include "../../Mesh.h"
#include "../../../Render/Engine/Rasterizer.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render
{

	class DrawSkyboxPass final : public IPass
	{
		Core::GraphicsContext* _context;
		Mesh _skybox_cube;
		Rasterizer _skybox_rasterizer;
		void execute() override;
	public:
		explicit DrawSkyboxPass(Core::GraphicsContext* context);
	};
}
