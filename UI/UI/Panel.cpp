#include "Panel.h"
#include "../Canvas/RenderEvent.h"
#include "Types/Types.h"

void UI::Panel::draw(Render::DrawEvent2D* event)
{	
	event->set_alpha(this->alpha);

	if (_texture)
		event->draw_rect(_position, _resolution, _texture);
	else
		event->draw_rect(_position, _resolution, _color);
}

UI::ElementDescription UI::Panel::get_desc()
{
	return ElementDescription(false, "PANEL");
}

UI::Panel::Panel(Vector2 position,Surface resolution, Render::GETexture* texture)
	: _position(position)
	, _resolution(resolution)
	, _texture(texture)
	, _color(1,1,1)
{}

UI::Panel::Panel(Vector2 position, Surface resolution, Color3XM color)
	: _position(position)
	, _resolution(resolution)
	, _texture(nullptr)
	, _color(color)
{}

bool UI::Panel::point_belongs(Position2 point)
{
	auto resolution = _resolution;
	auto position = _position;
	
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void UI::Panel::set_position(Position2 pos)
{
	_position = pos;
}

void UI::Panel::move_by(Position2 pos)
{
	_position += pos;
}

void UI::Panel::set_texture(Render::GETexture* texture)
{
	_texture = texture;
}

Position2 UI::Panel::get_position()
{
	return _position;
}


Surface UI::Panel::get_resolution()
{
	return _resolution;
}

void UI::Panel::set_resolution(Surface surface)
{
	_resolution = surface;
}
