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

void Render::TextComponent::set_text(wchar_t* text)
{
	auto length = wcslen(text);

	delete vbuffer;
	delete ibuffer;

	vbuffer = _device->alloc_vertex_buffer(length * GLYPH_VERTEX_SIZE);
	ibuffer = _device->alloc_index_buffer(6 * length);

	for(int i  =0 ;i < length;i++)
	{
		ibuffer->operator[](i * 6) = text_indices[0];
		ibuffer->operator[](i * 6 + 1) = text_indices[1];
		ibuffer->operator[](i * 6 + 2) = text_indices[2];
		ibuffer->operator[](i * 6 + 3) = text_indices[3];
		ibuffer->operator[](i * 6 + 4) = text_indices[4];
		ibuffer->operator[](i * 6 + 5) = text_indices[5];
	}
	ibuffer->update();

	auto texture_width = (float)font->font_texture->width();
	auto texture_height = (float)font->font_texture->height();

	for(auto i=0u;i<length;i++)
	{
		auto glyph = font->find_glyph(text[i]);

		vbuffer->at(i * 4) = Vertex(
			DirectX::XMFLOAT3(0,0,0),
			DirectX::XMFLOAT3(
				glyph.Subrect.x/texture_width,
				glyph.Subrect.y/texture_height,
				0.f
			),
			DirectX::XMFLOAT3(0,0,0)
		);
		vbuffer->at(i * 4+1) = Vertex(
			DirectX::XMFLOAT3(350, 0, 0),
			DirectX::XMFLOAT3(
				glyph.Subrect.z / texture_width,
				glyph.Subrect.y / texture_height,
				0.f
			),
			DirectX::XMFLOAT3(0, 0, 0)
		);
		vbuffer->at(i * 4 + 2) = Vertex(
			DirectX::XMFLOAT3(0, -350, 0),
			DirectX::XMFLOAT3(
				glyph.Subrect.x / texture_width,
				glyph.Subrect.w / texture_height,
				0.f
			),
			DirectX::XMFLOAT3(0, 0, 0)
		);
		vbuffer->at(i * 4 + 3) = Vertex(
			DirectX::XMFLOAT3(350, -350, 0),
			DirectX::XMFLOAT3(
				glyph.Subrect.z / texture_width,
				glyph.Subrect.w / texture_height,
				0.f
			),
			DirectX::XMFLOAT3(0, 0, 0)
		);
	}

	vbuffer->update();
}
