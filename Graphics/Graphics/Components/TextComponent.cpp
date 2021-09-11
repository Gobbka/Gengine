#include "TextComponent.h"

#include "../SpriteFont.h"
#include "../../Graphics.h"
#include "../../Render/d3d/Vertex.h"

#define GLYPH_VERTEX_SIZE 4

UINT text_indices[]
{
	0,1,2,1,3,2
};

Render::TextComponent::TextComponent(Core::GraphicsContext* context)
{
	_device = context->get_device();

	ibuffer = nullptr;
	vbuffer = nullptr;
}

Render::TextComponent::~TextComponent()
{
	delete vbuffer;
	delete ibuffer;
}

void Render::TextComponent::set_text(const wchar_t* text)
{
	auto length = wcslen(text);

	delete vbuffer;
	delete ibuffer;

	vbuffer = _device->alloc_vertex_buffer(length * GLYPH_VERTEX_SIZE);
	ibuffer = _device->alloc_index_buffer(6 * length);

	for(int i  =0 ;i < length;i++)
	{
		ibuffer->operator[](i * 6 + 0) = text_indices[0] + 4 * i;
		ibuffer->operator[](i * 6 + 1) = text_indices[1] + 4 * i;
		ibuffer->operator[](i * 6 + 2) = text_indices[2] + 4 * i;
		ibuffer->operator[](i * 6 + 3) = text_indices[3] + 4 * i;
		ibuffer->operator[](i * 6 + 4) = text_indices[4] + 4 * i;
		ibuffer->operator[](i * 6 + 5) = text_indices[5] + 4 * i;
	}
	ibuffer->update();

	auto texture_width = (float)font->font_texture->width();
	auto texture_height = (float)font->font_texture->height();

	Vector2 write_pos(0, 0);

	for(auto i=0u;i<length;i++)
	{
		auto glyph = font->find_glyph(text[i]);

		Vector2 glyphResolution(glyph.Subrect.z - glyph.Subrect.x , glyph.Subrect.w - glyph.Subrect.y);

		vbuffer->at(i * 4) = Vertex(
			DirectX::XMFLOAT3(write_pos.x + glyph.XOffset, write_pos.y - glyph.YOffset,0),
			DirectX::XMFLOAT3(
				glyph.Subrect.x/texture_width,
				glyph.Subrect.y/texture_height,
				0.f
			),
			DirectX::XMFLOAT3(0,0,0)
		);
		vbuffer->at(i * 4+1) = Vertex(
			DirectX::XMFLOAT3(write_pos.x + glyphResolution.x + glyph.XOffset, write_pos.y - glyph.YOffset, 0),
			DirectX::XMFLOAT3(
				glyph.Subrect.z / texture_width,
				glyph.Subrect.y / texture_height,
				0.f
			),
			DirectX::XMFLOAT3(0, 0, 0)
		);
		vbuffer->at(i * 4 + 2) = Vertex(
			DirectX::XMFLOAT3(write_pos.x + glyph.XOffset, write_pos.y - glyphResolution.y - glyph.YOffset, 0),
			DirectX::XMFLOAT3(
				glyph.Subrect.x / texture_width,
				glyph.Subrect.w / texture_height,
				0.f
			),
			DirectX::XMFLOAT3(0, 0, 0)
		);
		vbuffer->at(i * 4 + 3) = Vertex(
			DirectX::XMFLOAT3(write_pos.x + glyphResolution.x + glyph.XOffset, write_pos.y - glyphResolution.y - glyph.YOffset, 0),
			DirectX::XMFLOAT3(
				glyph.Subrect.z / texture_width,
				glyph.Subrect.w / texture_height,
				0.f
			),
			DirectX::XMFLOAT3(0, 0, 0)
		);

		write_pos.x += glyphResolution.x;
		if (text[i] == L'\n')
		{
			write_pos.x = 0;
			write_pos.y -= font->line_spacings;
		}
		if(text[i]==L' ')
		{
			write_pos.x += 8;
		}
	}

	vbuffer->update();
}
