#include "Button.h"
#include "../../InteractiveForm.h"
#include "../../Canvas/RenderEvent.h"

bool UI::Button::point_belongs(Position2 point)
{
	auto position = _position;
	auto resolution = _resolution;
	
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void UI::Button::set_position(Position2 position)
{
	_position = position;
}

void UI::Button::draw(Render::DrawEvent2D* event)
{
	event->draw_rect(_position, _resolution, _visible_color);
}

UI::ElementDescription UI::Button::get_desc()
{
	return ElementDescription(false,"BUTTON",true );
}

UI::Button::Button(Position2 position, Surface resolution, Color3XM color, const char* text)
	: _position(position)
	, _resolution(resolution)
	, _color(color)
	, _visible_color(color)
{

}

void UI::Button::set_color(Color3XM color)
{
	_color = color;
}

void UI::Button::move_by(Position2 offset)
{
	_position += offset;
}

void UI::Button::set_resolution(Surface resolution)
{
	_resolution = resolution;
}

Surface UI::Button::get_resolution()
{
	return _resolution;
}

void UI::Button::handle_mouse_up()
{
	this->onClick(this);

	_visible_color = { _color.r + .1f,_color.g + .1f,_color.b + 0.1f };

	InteractiveElement::handle_mouse_up();
}

void UI::Button::handle_mouse_down()
{
	_visible_color = { _visible_color.r + .2f,_visible_color.g + .2f,_visible_color.b + 0.2f };
	
	InteractiveElement::handle_mouse_down();
}

void UI::Button::handle_mouse_enter()
{
	_visible_color = { _color.r + .1f,_color.g + .1f,_color.b + 0.1f };

	InteractiveElement::handle_mouse_enter();
}

void UI::Button::handle_mouse_leave()
{
	_visible_color = _color;
	InteractiveElement::handle_mouse_leave();
}

void UI::Button::set_texture(Render::Texture* texture)
{
}

Position2 UI::Button::get_position()
{
	return _position;
}
