#pragma once
#include "../IPass/IPass.h"
#include "../../../Render/Common/GraphicsCommon.h"

namespace Render
{
	class CreateNormalsMapPass : public IPass
	{
		GEGraphics* _context;
		void execute(Scene*scene) override;
	public:
		CreateNormalsMapPass(GEGraphics*context)
			: _context(context)
		{}
	};
}
