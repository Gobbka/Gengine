#include "SpriteFont.h"
#include <BinaryReader.h>
#include <dxgiformat.h>
#include <exception>

#include "../Graphics.h"

static const char spriteFontMagic[] = "DXTKfont";

Render::SpriteFont::SpriteFont(IGDevice* device,BinaryReader& reader)
{
    // Validate the header.
    for (char const* magic = spriteFontMagic; *magic; magic++)
    {
        if (reader.Read<uint8_t>() != *magic)
        {
            throw std::exception("This is not sprite font");
        }
    }

    auto glyphCount = reader.Read<uint32_t>();
    auto* glyphData = reader.ReadArray<Glyph>(glyphCount);

    for(uint32_t i =0;i < glyphCount;i++)
    {
        glyphs.push_back(glyphData[i]);
    }

    line_spacings = reader.Read<float>();
    default_character = reader.Read<uint32_t>();

    auto textureWidth = reader.Read<uint32_t>();
    auto textureHeight = reader.Read<uint32_t>();
    auto textureFormat = reader.Read<DXGI_FORMAT>();
    auto textureStride = reader.Read<uint32_t>();
    auto textureRows = reader.Read<uint32_t>();

    uint64_t dataSize = uint64_t(textureStride) * uint64_t(textureRows);

    auto textureData = reader.ReadArray<uint8_t>(static_cast<size_t>(dataSize));

    this->font_texture = device->create_texture(
	    ITexture2DDesc {
            ITexture2DDesc::Usage::DEFAULT,
	        textureFormat,
    		textureWidth,
    		textureHeight,
    		textureStride,
    		textureRows,
    		(void*)textureData
	    }
    );
}

Render::SpriteFont::SpriteFont(IGDevice* device, const wchar_t* file_name)
{
    BinaryReader reader(file_name);
    *this = SpriteFont(device, reader);
}

Render::Glyph Render::SpriteFont::default_glyph()
{
    return glyphs[0];
}

Render::Glyph Render::SpriteFont::find_glyph(uint32_t character)
{
    for(const auto glyph : glyphs)
    {
        if (glyph.Character == character)
            return glyph;
    }
    
    return default_glyph();
}
