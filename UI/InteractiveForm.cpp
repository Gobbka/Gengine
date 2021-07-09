#include "InteractiveForm.h"
#include "elements/IElement/InteractiveElement.h"
#include <windowsx.h>

using namespace UI;

void InteractiveForm::render_components(Render::DrawEvent* event)
{
	for(auto*element:this->childs)
	{
		if (element->state.visible == UI::VISIBLE_STATE_VISIBLE)
			element->draw(event);
		
		event->mask_clear();
	}
}

void InteractiveForm::foreach(std::function<void(UI::InteractiveElement* element)> callback)
{
	for(auto*element:this->childs)
		callback(element);
}

void InteractiveForm::drag_move(InteractiveElement* element)
{
	auto pos = element->get_position();
	auto cursor = *_cursor_position;
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
	for (auto* in_element : this->childs)
		if (element == in_element)
			return true;
	return false;
}


InteractiveForm* InteractiveForm::add_element(UI::InteractiveElement* element)
{
	this->childs.push_back(element);
	element->initialize(this);
	return this;
}

InteractiveForm::InteractiveForm(Render::D3DEngine* pEngine, Position2* cursor_position)
	: Canvas2DLayer(pEngine)
{
	_cursor_position = cursor_position;
}

InteractiveForm::~InteractiveForm()
{
	
}

Interaction::EventStatus InteractiveForm::on_mouse_move(int mx,int my)
{
	if (this->hidden())
		return Interaction::EventStatus::none;

	const Position2 cursor = {(float)mx,(float)my * -1};

	if (this->dragged)
	{
		this->dragged->element->set_position(Position2(cursor.x - this->dragged->dragged_offset.x, cursor.y - this->dragged->dragged_offset.y));
		return Interaction::EventStatus::handled;
	}

	auto e_handled = Interaction::EventStatus::none;

	for (auto i = this->childs.size(); i --> 0;)
	{
		auto* element = this->childs[i];
		
		if (
			element->state.visible == UI::VISIBLE_STATE_VISIBLE &&
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
	if (this->hidden())
		return Interaction::EventStatus::none;
	
	this->foreach([direction](UI::InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_mouse_scroll(direction);
		});
	return Interaction::EventStatus::none;
}

Interaction::EventStatus InteractiveForm::on_lbmouse_up()
{
	if (this->hidden())
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
	if (this->hidden())
		return Interaction::EventStatus::none;
	
	this->foreach([](UI::InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_mouse_down();
		});
	return Interaction::EventStatus::none;
}

