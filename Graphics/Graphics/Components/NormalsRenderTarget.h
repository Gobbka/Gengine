#pragma once
#include "../../Render/Common/RenderTarget.h"

namespace Render
{

	struct __declspec(dllexport) LightViewer final
	{
		GERenderTarget normals_map;
		GERenderTarget light_map;

		LightViewer(Core::GraphicsContext*context,Surface resolution)
			: normals_map(context,resolution)
			, light_map(context,resolution)
		{
			normals_map.clear_color = { .5f,.5f,.5f,1.f };
			light_map.clear_color = {.5f,.5f,.5f,1.f};
		}
	};
}
