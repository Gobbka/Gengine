#pragma once
#include <vector>

#include "Types/Types.h"

namespace Core
{
	class GraphicsContext;
}

class BinaryReader;

namespace Render {

	struct Glyph
	{
		uint32_t Character;
		Vector4Int Subrect;
		float XOffset;
		float YOffset;
		float XAdvance;
	};

	class Texture;

	struct __declspec(dllexport) SpriteFont
	{
		std::vector<Glyph> glyphs;
		float line_spacings;
		wchar_t default_character;
		Texture* font_texture;

		SpriteFont(Core::GraphicsContext*context,BinaryReader& reader);
		SpriteFont(Core::GraphicsContext*context,const wchar_t*file_name);

		Glyph default_glyph();
		Glyph find_glyph(uint32_t character);
	};
}
