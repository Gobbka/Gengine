#pragma once
#include "../IPass/IPass.h"

namespace Render
{
	class CreateNormalsMapPass : public IPass
	{

		void execute(Core::GraphicsContext* context) override;
	};
}
