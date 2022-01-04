#pragma once
#include "../IPass/IPass.h"
#include "../../Mesh.h"
#include "../../../Render/Common/Rasterizer.h"

namespace Render
{
	class DrawSkyboxPass final : public IPass
	{
		Core::DX11Graphics* _context;
		Mesh _skybox_cube;
		GERasterizer _skybox_rasterizer;
		void execute(Scene*) override;
	public:
		explicit DrawSkyboxPass(Core::DX11Graphics* context);
	};
}
