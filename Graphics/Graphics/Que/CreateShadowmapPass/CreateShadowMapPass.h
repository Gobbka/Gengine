#pragma once
#include "../IPass/IPass.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	class Scene;

	class CreateShadowMapPass : public IPass
	{
		Core::GraphicsContext* _context;
		void execute(Scene*scene) override;
	public:
		CreateShadowMapPass(Core::GraphicsContext*context)
			: _context(context)
		{}

	};
}
