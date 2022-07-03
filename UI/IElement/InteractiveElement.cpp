#include "InteractiveElement.h"
#include "../InteractiveForm.h"

UI::ElementDescription::ElementDescription(bool can_be_parent, const char* string_name,bool has_text)
	: can_be_parent(can_be_parent)
	, has_text(has_text)
	, string_name(string_name)
{
}

bool UI::InteractiveElement::haveParent() const
{
	return this->parent != nullptr;
}

void UI::InteractiveElement::set_alpha(float alpha)
{
	styles.alpha = alpha;
}

UI::Parent* UI::InteractiveElement::parentNode() const
{
	return this->parent;
}

UI::InteractiveForm* UI::InteractiveElement::get_form() const
{
	return this->form;
}

Position2 UI::InteractiveElement::point_to(InteractiveElement* element)
{
	auto own_pos = get_position();
	auto their_pos = element->get_position();

	return Position2(own_pos.x - their_pos.x, own_pos.y - their_pos.y);
}

void UI::InteractiveElement::set_form(InteractiveForm* form)
{
	this->form = form;
}

void UI::InteractiveElement::set_parent(Parent* parent)
{
	this->parent = parent;
}

void UI::InteractiveElement::handleMouseMove(MouseEvent* event)
{
	event->target = this;
	if(onMouseMove)
	{
		this->onMouseMove(event);
	}
}

void UI::InteractiveElement::handleMouseLeave()
{
	this->state.hovered = false;
	if(onMouseLeave)
	{
		this->onMouseLeave(nullptr);
	}
}

void UI::InteractiveElement::handleMouseEnter()
{
	this->state.hovered = true;
	this->onMouseEnter(nullptr);
}

void UI::InteractiveElement::handleMouseUp(MouseEvent* event)
{
	event->target = this;
	if(onMouseUp)
	{
		this->onMouseUp(event);
	}
}

void UI::InteractiveElement::handleMouseDown(MouseEvent* event)
{
	event->target = this;
	this->onMouseDown(event);
}

void UI::InteractiveElement::handle_db_click()
{
	this->onDBClick(nullptr);
}

void UI::InteractiveElement::handle_mouse_scroll(MouseEvent* delta)
{
	this->onMouseScroll(delta);
}
