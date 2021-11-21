#include "Text.h"

#include <Graphics/SpriteFont.h>
#include <Graphics.h>

#include "../Canvas/RenderEvent.h"
#include "../Canvas/Vertex2D.h"

#define GLYPH_VERTEX_SIZE 4

UINT text_indices[]
{
	0,1,2,1,3,2
};

UI::Text::Text(Render::SpriteFont* font, const wchar_t* text)
	: _length(0)
	, _text(nullptr)
	, _vbuffer(nullptr)
	, _ibuffer(nullptr)
	, font(font)
{
	set_text(text);
}

UI::Text::Text(Text&& other) noexcept
	: _length(other._length)
	, _text(other._text)
	, _vbuffer(other._vbuffer)
	, _ibuffer(other._ibuffer)
	, font(other.font)
{
	other.font = nullptr;
	other._vbuffer = nullptr;
	other._ibuffer = nullptr;
	other._text = nullptr;
}

UI::Text& UI::Text::operator=(Text&& other) noexcept
{
	if (_vbuffer != other._vbuffer)
		delete _vbuffer;
	if (_ibuffer != other._ibuffer)
		delete _ibuffer;

	_text = other._text;
	_vbuffer = other._vbuffer;
	_ibuffer = other._ibuffer;
	_length = other._length;
	font = other.font;

	other.font = nullptr;
	other._vbuffer = nullptr;
	other._ibuffer = nullptr;
	other._text = nullptr;

	return*this;
}

UI::Text::~Text()
{
	delete _vbuffer;
	delete _ibuffer;
}

void UI::Text::set_text(const wchar_t* text)
{
	_length = wcslen(text);

	delete _vbuffer;
	delete _ibuffer;

	_vbuffer = new Vertex2D[_length * GLYPH_VERTEX_SIZE];
	_ibuffer = new unsigned[6 * _length];

	for(int i  =0 ;i < _length;i++)
	{
		_ibuffer[i * 6 + 0] = text_indices[0] + 4 * i;
		_ibuffer[i * 6 + 1] = text_indices[1] + 4 * i;
		_ibuffer[i * 6 + 2] = text_indices[2] + 4 * i;
		_ibuffer[i * 6 + 3] = text_indices[3] + 4 * i;
		_ibuffer[i * 6 + 4] = text_indices[4] + 4 * i;
		_ibuffer[i * 6 + 5] = text_indices[5] + 4 * i;
	}

	const auto texture_width = (float)font->font_texture->width();
	const auto texture_height = (float)font->font_texture->height();

	Vector2 write_pos(0, 0);

	for(auto i=0u;i< _length;i++)
	{
		auto glyph = font->find_glyph(text[i]);

		Vector2 glyphResolution(glyph.Subrect.z - glyph.Subrect.x , glyph.Subrect.w - glyph.Subrect.y);

		_vbuffer[i * 4] = Vertex2D(
			Position2(write_pos.x + glyph.XOffset, write_pos.y - glyph.YOffset),
			Color3XM(1,1,1),
			Position2(
				glyph.Subrect.x/texture_width,
				glyph.Subrect.y/texture_height
			)
		);
		_vbuffer[i * 4+1] = Vertex2D(
			Position2(write_pos.x + glyphResolution.x + glyph.XOffset, write_pos.y - glyph.YOffset),
			Color3XM(1,1,1),
			Position2(
				glyph.Subrect.z / texture_width,
				glyph.Subrect.y / texture_height
			)
		);
		_vbuffer[i * 4 + 2] = Vertex2D(
			Position2(write_pos.x + glyph.XOffset, write_pos.y - glyphResolution.y - glyph.YOffset),
			Color3XM(1,1,1),
			Position2(
				glyph.Subrect.x / texture_width,
				glyph.Subrect.w / texture_height
			)
		);
		_vbuffer[i * 4 + 3] = Vertex2D(
			Position2(write_pos.x + glyphResolution.x + glyph.XOffset, write_pos.y - glyphResolution.y - glyph.YOffset),
			Color3XM(1,1,1),
			Position2(
				glyph.Subrect.z / texture_width,
				glyph.Subrect.w / texture_height
			)
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
}

void UI::Text::set_position(Position2 pos)
{

}

void UI::Text::set_resolution(Surface surface)
{

}

void UI::Text::set_texture(Render::Texture* texture)
{
}

void UI::Text::move_by(Position2)
{
}

void UI::Text::draw(Render::DrawEvent2D* event)
{
	const auto draw_cmd = event->new_draw_cmd(_length * GLYPH_VERTEX_SIZE,_length*6,font->font_texture);

	memcpy(draw_cmd.vertices, _vbuffer, _length * GLYPH_VERTEX_SIZE * sizeof(Vertex2D));
	memcpy(draw_cmd.indices, _ibuffer, _length * 6 * sizeof(UINT));

}

Position2 UI::Text::get_position()
{
	return { 0,0 };
}

UI::ElementDescription UI::Text::get_desc()
{
	return { false,"LABEL" };
}

Surface UI::Text::get_resolution()
{
	return { 0,0 };
}

bool UI::Text::point_belongs(Position2 point)
{
	return false;
}