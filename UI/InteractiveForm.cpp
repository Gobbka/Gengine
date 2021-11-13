#include "InteractiveForm.h"

#include <iostream>

#include "elements/IElement/InteractiveElement.h"
#include <windowsx.h>

using namespace UI;

void InteractiveForm::render_components(Render::DrawEvent2D* event)
{
	for(auto*element:this->_childs)
	{
		if (element->styles.display != ElementStyles::DisplayType::none)
			element->draw(event);
	}
}

void InteractiveForm::foreach(std::function<void(UI::InteractiveElement* element)> callback)
{
	for(auto*element:this->_childs)
		callback(element);
}

void InteractiveForm::drag_move(InteractiveElement* element)
{
	auto pos = element->get_position();
	auto cursor = *_cursor_position;

	pos.y *= -1;
	cursor -= pos;
	this->dragged = new DragStruct{ cursor ,element};
}

void InteractiveForm::free_drag_move()
{
	if (this->dragged == nullptr) return;

	delete this->dragged;
	this->dragged = nullptr;
}

bool InteractiveForm::has_element(UI::InteractiveElement* element)
{
	for (auto* in_element : this->_childs)
		if (element == in_element)
			return true;
	return false;
}


InteractiveForm* InteractiveForm::add_element(UI::InteractiveElement* element)
{
	this->_childs.push_back(element);
	element->initialize(this);
	return this;
}

InteractiveForm::InteractiveForm(Core::GraphicsContext* pEngine, Position2* cursor_position)
	: _canvas(pEngine)
{
	_cursor_position = cursor_position;
}

//InteractiveForm::InteractiveForm(InteractiveForm&& other) noexcept
//	: Canvas((Canvas)other)
//{
//
//}

InteractiveForm::~InteractiveForm()
{
	
}

Interaction::EventStatus InteractiveForm::on_mouse_move(int mx,int my)
{
	if (hidden())
		return Interaction::EventStatus::none;

	const Position2 cursor = {(float)mx,(float)my * -1};

	if (this->dragged)
	{
		this->dragged->element->set_position(Position2(cursor.x - this->dragged->dragged_offset.x, cursor.y + this->dragged->dragged_offset.y));
		return Interaction::EventStatus::handled;
	}

	auto e_handled = Interaction::EventStatus::none;

	for (auto i = this->_childs.size(); i --> 0;)
	{
		auto* element = this->_childs[i];
		
		if (
			element->styles.display != ElementStyles::DisplayType::none &&
			e_handled == Interaction::EventStatus::none &&
			element->point_belongs(cursor)
			)
		{
			if (element->state.hovered == false)
			{
				element->handle_mouse_enter();
			}
			element->handle_mouse_move(cursor.x, cursor.y);
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
	
	this->foreach([direction](UI::InteractiveElement* element)
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

	this->foreach([](UI::InteractiveElement* element)
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

void InteractiveForm::update()
{
	if (!hidden())
		_canvas.update();
}

void InteractiveForm::render(Render::DrawEvent2D* event)
{
	if(!hidden())
		_canvas.render(event);
}

Canvas::Canvas* InteractiveForm::canvas()
{
	return &_canvas;
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

