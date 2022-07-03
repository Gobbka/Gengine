#include "Checkbox.h"
#include "../Canvas/RenderEvent.h"

void UI::Checkbox::draw(Render::DrawEvent2D* event)
{
	if (*_lp_value)
		event->drawRect(_position, _resolution, active_color);
	else
		event->drawRect(_position, _resolution, non_active_color);
}

bool UI::Checkbox::is_checked() const
{
	return *_lp_value;
}

UI::ElementDescription UI::Checkbox::getDesc()
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

void UI::Checkbox::setPosition(const Position2 position)
{
	_position = position;
}

Position2 UI::Checkbox::getPosition()
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

bool UI::Checkbox::pointBelongs(const Position2 point)
{
	const auto position = getPosition();
	const auto resolution = get_resolution();
	
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void UI::Checkbox::moveBy(const Position2 offset)
{
	_position += offset;
}

void UI::Checkbox::handleMouseUp(MouseEvent* event)
{
	*_lp_value = !*_lp_value;

	InteractiveElement::handleMouseUp(event);
}

void UI::Checkbox::set_texture(Render::GETexture* texture)
{

}
