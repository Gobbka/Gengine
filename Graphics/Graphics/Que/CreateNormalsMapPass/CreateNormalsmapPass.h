#pragma once
#include "../IPass/IPass.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	class Scene;

	class CreateNormalsMapPass : public IPass
	{
		Core::GraphicsContext* _context;
		void execute(Scene*scene) override;
	public:
		CreateNormalsMapPass(Core::GraphicsContext*context)
			: _context(context)
		{}
	};
}
