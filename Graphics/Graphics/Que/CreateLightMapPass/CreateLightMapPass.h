#pragma once
#include "../IPass/IPass.h"
#include "../../Mesh.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	class Scene;

	class CreateLightMapPass : public IPass
	{
		Mesh _point_light_cube;
		Core::GraphicsContext* _context;
		void execute(Scene*scene) override;
	public:
		explicit CreateLightMapPass(Core::GraphicsContext* context);
	};
}
