#include "Button.h"
#include "../InteractiveForm.h"
#include "../Canvas/RenderEvent.h"

bool UI::Button::pointBelongs(Position2 point)
{
	const auto position = _position;
	const auto resolution = _resolution;
	
	return
		(point.x >= position.x && point.x <= position.x + resolution.width) &&
		(point.y <= position.y && point.y >= (position.y - resolution.height));
}

void UI::Button::setPosition(Position2 position)
{
	_position = position;
	_text.setPosition(position);
}

void UI::Button::draw(Render::DrawEvent2D* event)
{
	event->drawRect(_position, _resolution, _visible_color);
	_text.draw(event);
}

UI::ElementDescription UI::Button::getDesc()
{
	return {false,"BUTTON",true};
}

UI::Button::Button(Position2 position, Surface resolution, Color3XM color,Render::SpriteFont*font, const wchar_t* text)
	: _position(position)
	, _resolution(resolution)
	, _color(color)
	, _visible_color(color)
	, _text(font,text,position)
{
	styles.cursor = Css::Cursor::pointer;
}

void UI::Button::set_color(Color3XM color)
{
	_color = color;
}

void UI::Button::set_text_color(Color3XM color)
{
	_text.set_color(color);
}

void UI::Button::moveBy(Position2 offset)
{
	_position += offset;
	_text.moveBy(offset);
}

void UI::Button::set_resolution(Surface resolution)
{
	_resolution = resolution;
}

Surface UI::Button::get_resolution()
{
	return _resolution;
}

void UI::Button::handleMouseUp(MouseEvent* event)
{
	event->target = this;
	this->onClick(event);

	_visible_color = { _color.r + .1f,_color.g + .1f,_color.b + 0.1f };

	InteractiveElement::handleMouseUp(event);
}

void UI::Button::handleMouseDown(MouseEvent* event)
{
	_visible_color = { _visible_color.r + .2f,_visible_color.g + .2f,_visible_color.b + 0.2f };
	
	InteractiveElement::handleMouseDown(event);
}

void UI::Button::handleMouseEnter()
{
	_visible_color = { _color.r + .1f,_color.g + .1f,_color.b + 0.1f };

	InteractiveElement::handleMouseEnter();
}

void UI::Button::handleMouseLeave()
{
	_visible_color = _color;

	InteractiveElement::handleMouseLeave();
}

void UI::Button::set_texture(Render::GETexture* texture)
{
}

Position2 UI::Button::getPosition()
{
	return _position;
}
