#pragma once
#include "../IPass/IPass.h"
#include "../../../Render/Common/GraphicsCommon.h"

namespace Render
{
	class CreateShadowMapPass : public IPass
	{
		GEGraphics* _context;
		void execute(Scene*scene) override;
	public:
		CreateShadowMapPass(GEGraphics*context)
			: _context(context)
		{}

	};
}
