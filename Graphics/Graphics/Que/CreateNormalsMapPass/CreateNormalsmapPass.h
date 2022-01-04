#pragma once
#include "../IPass/IPass.h"

namespace Core
{
	class DX11Graphics;
}

namespace Render
{
	class CreateNormalsMapPass : public IPass
	{
		Core::DX11Graphics* _context;
		void execute(Scene*scene) override;
	public:
		CreateNormalsMapPass(Core::DX11Graphics*context)
			: _context(context)
		{}
	};
}
