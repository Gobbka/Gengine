#include "SpriteFont.h"
#include <BinaryReader.h>
#include <dxgiformat.h>
#include <exception>
#include <Windows.h>

#include "../Graphics.h"
#include "Material/Material.h"

static const char spriteFontMagic[] = "DXTKfont";

struct Glyph
{
    uint32_t Character;
    RECT Subrect;
    float XOffset;
    float YOffset;
    float XAdvance;
};

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
    auto glyphData = reader.ReadArray<Glyph>(glyphCount);

    line_spacings = reader.Read<float>();
    default_character = reader.Read<uint32_t>();

    auto textureWidth = reader.Read<uint32_t>();
    auto textureHeight = reader.Read<uint32_t>();
    auto textureFormat = reader.Read<DXGI_FORMAT>();
    auto textureStride = reader.Read<uint32_t>();
    auto textureRows = reader.Read<uint32_t>();

    uint64_t dataSize = uint64_t(textureStride) * uint64_t(textureRows);

    auto textureData = reader.ReadArray<uint8_t>(static_cast<size_t>(dataSize));

    Material mat((BYTE*)textureData, Surface(textureWidth, textureHeight));
    mat.format = textureFormat;
    this->font_texture = context->get_device()->create_texture(mat);
}
