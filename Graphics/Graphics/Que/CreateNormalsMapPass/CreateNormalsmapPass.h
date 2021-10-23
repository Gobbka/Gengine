#pragma once
#include "../IPass/IPass.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	class CreateNormalsMapPass : public IPass
	{
		Core::GraphicsContext* _context;
		void execute() override;
	public:
		CreateNormalsMapPass(Core::GraphicsContext*context)
			: _context(context)
		{}
	};
}
