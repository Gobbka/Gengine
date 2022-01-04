#include "Checkbox.h"
#include "../Canvas/RenderEvent.h"

void UI::Checkbox::draw(Render::DrawEvent2D* event)
{
	if (*_lp_value)
		event->draw_rect(_position, _resolution, active_color);
	else
		event->draw_rect(_position, _resolution, non_active_color);
}

bool UI::Checkbox::is_checked() const
{
	return *_lp_value;
}

UI::ElementDescription UI::Checkbox::get_desc()
{
	return ElementDescription(false,"CHECKBOX" );
}

UI::Checkbox::Checkbox(Position2 position, Surface resolution, Color3XM color, bool* value)
	: _lp_value(value)
	, _position(position)
	, _resolution(resolution)
	, active_color(color)
{}

UI::Checkbox::Checkbox(const Position2 position, const Surface resolution,bool*value)
	: _lp_value(value)
	, _position(position)
	, _resolution(resolution)
{}

void UI::Checkbox::set_position(const Position2 position)
{
	_position = position;
}

Position2 UI::Checkbox::get_position()
{
	return _position;
}

Surface UI::Checkbox::get_resolution()
{
	return _resolution;
}

void UI::Checkbox::set_resolution(const Surface resolution)
{
	_resolution = resolution;
}

bool UI::Checkbox::point_belongs(const Position2 point)
{
	const auto position = get_position();
	const auto resolution = get_resolution();
	
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void UI::Checkbox::move_by(const Position2 offset)
{
	_position += offset;
}

void UI::Checkbox::handle_mouse_up()
{
	*_lp_value = !*_lp_value;

	InteractiveElement::handle_mouse_up();
}

void UI::Checkbox::set_texture(Render::GETexture* texture)
{

}
