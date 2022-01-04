#include "InteractiveForm.h"

#include <iostream>

#include "IElement/InteractiveElement.h"
#include "Canvas/RenderEvent.h"

using namespace UI;

void InteractiveForm::foreach(std::function<void(UI::InteractiveElement* element)> callback)
{
	for(auto*element:this->_children)
		callback(element);
}

void InteractiveForm::drag_move(InteractiveElement* element)
{
	auto pos = element->get_position();
	auto cursor = *_cursor_position;

	pos.y *= -1;
	cursor -= pos;
	dragged = new DragStruct{ cursor ,element};
}

void InteractiveForm::free_drag_move()
{
	if (dragged == nullptr) return;

	delete dragged;
	dragged = nullptr;
}

bool InteractiveForm::has_element(UI::InteractiveElement* element)
{
	for (auto* in_element : this->_children)
		if (element == in_element)
			return true;
	return false;
}


InteractiveForm* InteractiveForm::add_element(UI::InteractiveElement* element)
{
	_children.push_back(element);

	return this;
}

InteractiveForm::InteractiveForm(Core::DX11Graphics* pEngine, Position2* cursor_position)
	: _hidden(false)
	, _canvas(pEngine)
	, _cursor_position(cursor_position)
{}

Interaction::EventStatus InteractiveForm::on_mouse_move(MoveEvent move_event)
{
	if (hidden())
		return Interaction::EventStatus::none;

	if (this->dragged)
	{
		auto new_pos = dragged->element->get_position() + move_event.delta;
		this->dragged->element->set_position(new_pos);
		return Interaction::EventStatus::handled;
	}

	auto e_handled = Interaction::EventStatus::none;

	for (auto i = this->_children.size(); i --> 0;)
	{
		auto* element = this->_children[i];
		
		if (
			element->styles.display != ElementStyles::DisplayType::none &&
			e_handled == Interaction::EventStatus::none &&
			element->point_belongs(move_event.absolute)
			)
		{
			if (element->state.hovered == false)
			{
				element->handle_mouse_enter();
			}
			element->handle_mouse_move(move_event);
			e_handled = Interaction::EventStatus::handled;
		}
		else if (element->state.hovered == true)
		{
			element->handle_mouse_leave();
		}
	}

	return e_handled;
}

Interaction::EventStatus InteractiveForm::on_mouse_scroll(short direction)
{
	if (hidden())
		return Interaction::EventStatus::none;
	
	foreach([direction](UI::InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_mouse_scroll(direction);
		});
	return Interaction::EventStatus::none;
}

Interaction::EventStatus InteractiveForm::on_db_click()
{
	if (hidden())
		return Interaction::EventStatus::none;

	foreach([](UI::InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_db_click();
		});
	return Interaction::EventStatus::none;
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

	for (auto* element : this->_children)
	{
		if (element->styles.display != ElementStyles::DisplayType::none)
			element->draw(&event);
	}

	_canvas.present();
}

Interaction::EventStatus InteractiveForm::on_lbmouse_up()
{
	if (hidden())
		return Interaction::EventStatus::none;
	
	this->foreach([](UI::InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_mouse_up();
		});

	this->free_drag_move();

	return Interaction::EventStatus::none;
}

Interaction::EventStatus InteractiveForm::on_lbmouse_down()
{
	if (hidden())
		return Interaction::EventStatus::none;
	
	this->foreach([](UI::InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_mouse_down();
		});
	return Interaction::EventStatus::none;
}

