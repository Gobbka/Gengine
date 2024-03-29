#include "InteractiveForm.h"

#include <iostream>

#include "IElement/InteractiveElement.h"
#include "Canvas/RenderEvent.h"

using namespace UI;

void InteractiveForm::foreach(std::function<void(InteractiveElement* element)> callback) const
{
	for(auto* element : _children)
		callback(element);
}

void InteractiveForm::drag_move(InteractiveElement* element)
{
	auto pos = element->get_position();
	auto cursor = *_cursor_position;

	pos.y *= -1;
	cursor -= pos;
	_dragged = new DragStruct{ cursor ,element};
}

void InteractiveForm::free_drag_move()
{
	if (_dragged == nullptr) return;

	delete _dragged;
	_dragged = nullptr;
}

bool InteractiveForm::has_element(InteractiveElement* element) const
{
	for (auto* in_element : _children)
		if (element == in_element)
			return true;
	return false;
}


InteractiveForm* InteractiveForm::add_element(InteractiveElement* element)
{
	_children.push_back(element);

	return this;
}

InteractiveForm::InteractiveForm(Render::GEGraphics* pEngine, Position2* cursor_position)
	: _hidden(false)
	, _canvas(pEngine)
	, _cursor_position(cursor_position)
{}

EventStatus InteractiveForm::on_mouse_move(MoveEvent move_event) const
{
	if (hidden())
		return EventStatus::none;

	if (_dragged)
	{
		const auto new_pos = _dragged->element->get_position() + move_event.delta;
		_dragged->element->set_position(new_pos);
		return EventStatus::handled;
	}

	auto e_handled = EventStatus::none;

	for (auto i = _children.size(); i --> 0;)
	{
		auto* element = _children[i];
		
		if (
			element->styles.display != ElementStyles::DisplayType::none &&
			e_handled == EventStatus::none &&
			element->point_belongs(move_event.absolute)
			)
		{
			if (element->state.hovered == false)
			{
				element->handle_mouse_enter();
			}
			element->handle_mouse_move(move_event);
			e_handled = EventStatus::handled;
		}
		else if (element->state.hovered == true)
		{
			element->handle_mouse_leave();
		}
	}

	return e_handled;
}

EventStatus InteractiveForm::on_mouse_scroll(short direction) const
{
	if (hidden())
		return EventStatus::none;
	
	foreach([direction](InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_mouse_scroll(direction);
		});
	return EventStatus::none;
}

EventStatus InteractiveForm::on_db_click() const
{
	if (hidden())
		return EventStatus::none;

	foreach([](InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_db_click();
		});
	return EventStatus::none;
}

bool InteractiveForm::hidden() const
{
	return _hidden;
}

void InteractiveForm::show()
{
	_hidden = false;
}

void InteractiveForm::hide()
{
	_hidden = true;
}

void InteractiveForm::render()
{
	auto* de = _canvas.begin();
	Render::DrawEvent2D event(_canvas.gfx(),de);

	for (auto* element : _children)
	{
		if (element->styles.display != ElementStyles::DisplayType::none)
			element->draw(&event);
	}

	_canvas.present();
}

EventStatus InteractiveForm::on_lbmouse_up()
{
	if (hidden())
		return EventStatus::none;

	for(auto*element : _children)
	{
		if (element->state.hovered == true)
			element->handle_mouse_up();
	}

	free_drag_move();

	return EventStatus::none;
}

EventStatus InteractiveForm::on_lbmouse_down() const
{
	if (hidden())
		return EventStatus::none;

	for(auto* element : _children)
	{
		if (element->state.hovered == true)
			element->handle_mouse_down();
	}

	return EventStatus::none;
}

