#pragma once


namespace Core
{
	class GraphicsContext;
}

class BinaryReader;

namespace Render {
	class Texture;

	struct __declspec(dllexport) SpriteFont
	{
		float line_spacings;
		wchar_t default_character;
		Texture* font_texture;

		SpriteFont(Core::GraphicsContext*context,BinaryReader& reader);
	};
}
