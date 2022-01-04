#pragma once

#include "../../Render/Common/Texture.h"

struct SkyboxComponent
{
	Render::GETexture* sky_texture;

	SkyboxComponent(Render::GETexture* sky_texture)
		: sky_texture(sky_texture)
	{}
};
