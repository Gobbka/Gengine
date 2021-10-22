#pragma once
#include "../../Render/Engine/RenderTarget.h"

namespace Render
{

	struct __declspec(dllexport) NormalsRenderTarget final : RenderTarget
	{
		NormalsRenderTarget(Core::GraphicsContext*context,Surface resolution)
			: RenderTarget(context,resolution)
		{
			clear_color = { 0.5,0.5,0.5,1 };
		}
	};
}
