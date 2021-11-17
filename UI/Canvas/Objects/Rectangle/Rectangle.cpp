#include "Rectangle.h"
#include "../../../Events/RenderEvent.h"
#include "../../Vertex2D.h"
#include <Render/Engine/SpriteEngine.h>
#include <Render/d3d/Buffer/Texture.h>

Canvas::INDEX Canvas::Rectangle::size()
{
	return 4;
}

void Canvas::Rectangle::apply_rectangle()
{
	if (canvas() == nullptr)
		return;
	
	auto* ptr = vertices();

	auto x = _position.x;
	auto y = _position.y;
	auto width = _resolution.width;
	auto height = _resolution.height;
	
	ptr[0].pos = Position2(x, y);
	ptr[1].pos = Position2(x + width, y);
	ptr[2].pos = Position2(x, y - height);
	ptr[3].pos = Position2(x + width, y - height);
}

void Canvas::Rectangle::apply_color()
{
	if (canvas() == nullptr)
		return;
	
	auto* ptr = vertices();

	ptr[0].color = Color3XM::white();//{ 1,1,1 };
	ptr[1].color = Color3XM::white();
	ptr[2].color = Color3XM::white();
	ptr[3].color = Color3XM::white();

	ptr[0].uv = { 0,0 };
	ptr[1].uv = { 1,0 };
	ptr[2].uv = { 0,1 };
	ptr[3].uv = { 1,1 };
}

void Canvas::Rectangle::on_initialize()
{
	apply_rectangle();
	apply_color();
}

Canvas::Rectangle::Rectangle(Render::Texture* background, Position2 position, Surface resolution)
	: _background_texture(background),
	_position(position),
	_resolution(resolution)
{}


void Canvas::Rectangle::draw(Render::DrawEvent2D* draw_event)
{
	if(_background_texture)
	{
		auto* sprite = draw_event->sprite_engine();

		sprite->bind_texture(_background_texture, 0);
		draw_event->draw_vertex(4);

	}
}

void Canvas::Rectangle::set_position(Position2 pos)
{
	_position = pos;
	
	apply_rectangle();
}

Position2 Canvas::Rectangle::get_position()
{
	return _position;
}

void Canvas::Rectangle::set_resolution(Surface surface)
{
	_resolution = surface;

	apply_rectangle();
}

Surface Canvas::Rectangle::get_resolution()
{
	return _resolution;
}

void Canvas::Rectangle::move_by(Position2 pos)
{
	_position += pos;

	apply_rectangle();
}

void Canvas::Rectangle::set_texture(Render::Texture* texture)
{
	_background_texture = texture;

	apply_color();
}
