#include "InteractiveElement.h"
#include "../../InteractiveForm.h"

UI::ElementDescription::ElementDescription(bool can_be_parent, const char* string_name,bool has_text)
{
	this->can_be_parent = can_be_parent;
	this->string_name = string_name;
	this->has_text = has_text;
}

bool UI::InteractiveElement::have_parent() const
{
	return this->parent != nullptr;
}

void UI::InteractiveElement::set_alpha(float alpha)
{
	this->alpha = alpha;
}

void UI::InteractiveElement::set_margin(float x, float y)
{
	this->styles.margin.x = this->styles.margin.z = x;
	this->styles.margin.y = this->styles.margin.w = y;
}

void UI::InteractiveElement::set_margin(float x, float y, float z, float w)
{
	this->styles.margin = { x,y,z,w };
}

void UI::InteractiveElement::initialize(InteractiveForm* form)
{
	this->form = form;
	this->on_initialize();
}

UI::Parent* UI::InteractiveElement::get_parent() const
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

void UI::InteractiveElement::set_parent(Parent* parent)
{
	this->parent = parent;
}

#pragma region events handler

void UI::InteractiveElement::handle_mouse_move( float mX, float mY)
{
	this->onMouseMove(this, mX, mY);
}

void UI::InteractiveElement::handle_mouse_leave()
{
	this->state.hovered = false;
	this->onMouseLeave(this);
}

void UI::InteractiveElement::handle_mouse_enter()
{
	this->state.hovered = true;
	this->onMouseEnter(this);
}

void UI::InteractiveElement::handle_mouse_up()
{
	this->onMouseUp(this);
}

void UI::InteractiveElement::handle_mouse_down()
{
	this->onMouseDown(this);
}

void UI::InteractiveElement::handle_db_click()
{
	this->onDBClick(this);
}

void UI::InteractiveElement::handle_mouse_scroll(int delta)
{
	this->onMouseScroll(this, delta);
}

#pragma endregion 

