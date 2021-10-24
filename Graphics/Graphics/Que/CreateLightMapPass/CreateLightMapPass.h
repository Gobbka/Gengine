#pragma once
#include "../IPass/IPass.h"
#include "../../Mesh.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	class VertexBuffer;

	class CreateLightMapPass : public IPass
	{
		Mesh _point_light_cube;
		Core::GraphicsContext* _context;
		void execute() override;
	public:
		explicit CreateLightMapPass(Core::GraphicsContext* context);
	};
}
