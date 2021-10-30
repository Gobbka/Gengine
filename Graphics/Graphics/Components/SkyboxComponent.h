#pragma once

namespace Render
{
	class Texture;
}

struct SkyboxComponent
{
	Render::Texture* sky_texture;

	SkyboxComponent(Render::Texture* sky_texture)
		: sky_texture(sky_texture)
	{}
};
