#pragma once
#include "../IPass/IPass.h"

namespace Render
{
	class CreateShadowMapPass : public IPass
	{
		void execute(Core::GraphicsContext* context) override;
	};
}
