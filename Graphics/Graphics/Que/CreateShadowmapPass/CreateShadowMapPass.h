#pragma once
#include "../IPass/IPass.h"

namespace Core
{
	class DX11Graphics;
}

namespace Render
{
	class CreateShadowMapPass : public IPass
	{
		Core::DX11Graphics* _context;
		void execute(Scene*scene) override;
	public:
		CreateShadowMapPass(Core::DX11Graphics*context)
			: _context(context)
		{}

	};
}
