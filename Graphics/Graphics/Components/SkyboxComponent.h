#pragma once
#include "../../Render/Common/GraphicsCommon.h"

namespace Render
{
	struct SkyboxComponent
	{
		GETexture* sky_texture;

		SkyboxComponent(GETexture* sky_texture)
			: sky_texture(sky_texture)
		{}
	};
}
