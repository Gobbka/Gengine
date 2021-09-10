#include "SpriteFont.h"
#include <BinaryReader.h>
#include <dxgiformat.h>
#include <exception>

#include "../Graphics.h"

static const char spriteFontMagic[] = "DXTKfont";

Render::SpriteFont::SpriteFont(Core::GraphicsContext* context,BinaryReader& reader)
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

    ITexture2DDesc desc;
    desc.pSysMem = (void*)textureData;
    desc.rows = textureRows;
    desc.stride = textureStride;
    desc.format = textureFormat;
    desc.height = textureHeight;
    desc.width = textureWidth;

    this->font_texture = context->get_device()->create_texture(desc);

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
