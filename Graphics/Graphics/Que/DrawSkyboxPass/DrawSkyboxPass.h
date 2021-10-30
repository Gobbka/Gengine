#pragma once
#include "../IPass/IPass.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	class DrawSkyboxPass : public IPass
	{
		Core::GraphicsContext* _context;
		void execute() override;
	public:
		DrawSkyboxPass(Core::GraphicsContext* context)
			: _context(context)
		{}
	};
}
