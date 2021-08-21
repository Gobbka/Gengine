#pragma once

namespace Render
{
	class Texture;

	struct TextureComponent
	{
		Texture* texture;

		TextureComponent(Texture* texture) : texture(texture) {}
	};
}
