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

    const auto glyphCount = reader.Read<uint32_t>();
    auto* glyphData = reader.ReadArray<Glyph>(glyphCount);

    for(uint32_t i =0;i < glyphCount;i++)
    {
        glyphs.push_back(glyphData[i]);
    }

    line_spacings = reader.Read<float>();
    default_character = reader.Read<uint32_t>();

    const auto textureWidth = reader.Read<uint32_t>();
    const auto textureHeight = reader.Read<uint32_t>();
    const auto textureFormat = reader.Read<DXGI_FORMAT>();
    const auto textureStride = reader.Read<uint32_t>();
    const auto textureRows = reader.Read<uint32_t>();

    const auto dataSize = uint64_t(textureStride) * uint64_t(textureRows);

    const auto textureData = reader.ReadArray<uint8_t>(static_cast<size_t>(dataSize));

    this->font_texture = device->create_texture(
	    ITexture2DDesc {
            ITexture2DDesc::Usage::DEFAULT,
            D3D11_BIND_SHADER_RESOURCE,
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
	:
	line_spacings(0),
	default_character(0),
	font_texture(nullptr)
{
    BinaryReader reader(file_name);
    if (!reader.valid())
        throw "Cannot read sprite file";

    *this = SpriteFont(device, reader);
}

Render::SpriteFont::SpriteFont(SpriteFont&& other) noexcept
{
    this->font_texture = other.font_texture;
    this->default_character = other.default_character;
    this->glyphs = other.glyphs;
    this->line_spacings = other.line_spacings;

    other.glyphs.clear();
    other.font_texture = nullptr;
}

Render::SpriteFont& Render::SpriteFont::operator=(SpriteFont&& other) noexcept
{
    if(font_texture != other.font_texture)
		delete font_texture;

    this->font_texture = other.font_texture;
    this->default_character = other.default_character;
    this->glyphs = other.glyphs;
    this->line_spacings = other.line_spacings;

    other.glyphs.clear();
    other.font_texture = nullptr;

    return *this;
}

Render::SpriteFont::~SpriteFont()
{
    delete font_texture;
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
