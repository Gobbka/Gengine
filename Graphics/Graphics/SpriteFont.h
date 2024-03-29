﻿#pragma once
#include <vector>
#include "Types/Types.h"
#include "../Render/Common/Texture.h"

class BinaryReader;

namespace Render {
	class IAllocator;

	struct Glyph
	{
		uint32_t Character;
		Vector4Int Subrect;
		float XOffset;
		float YOffset;
		float XAdvance;
	};

	struct __declspec(dllexport) SpriteFont
	{
		std::vector<Glyph> glyphs;
		float line_spacings;
		wchar_t default_character;
		GETexture* font_texture;

		SpriteFont(IAllocator*device,BinaryReader& reader);
		SpriteFont(IAllocator*device,const wchar_t*file_name);
		SpriteFont(SpriteFont&& other) noexcept;
		SpriteFont& operator=(SpriteFont&& other) noexcept;

		~SpriteFont();

		Glyph default_glyph();
		Glyph find_glyph(uint32_t character);
	};
}
