#include "Parentable.h"
#include "../InteractiveForm.h"

void UI::ChildrenCollection::foreach(std::function<void(UI::InteractiveElement* element)> iterator) const
{
	for(auto*element: _children)
		iterator(element);
}

void UI::ChildrenCollection::append(UI::InteractiveElement* child)
{
	_children.push_back(child);
}

size_t UI::ChildrenCollection::count() const
{
	return _children.size();
}

UI::InteractiveElement* UI::ChildrenCollection::operator[](UINT index)
{
	return _children[index];
}

UI::InteractiveElement* UI::ChildrenCollection::last()
{
	const auto _size = count();
	if (count() == 0)
		return nullptr;
	
	return _children[_size - 1];
}


void UI::Parent::handle_mouse_up()
{
	for(auto*element:_children)
	{
		if (element->state.hovered)
			element->handle_mouse_up();
	}
	
	InteractiveElement::handle_mouse_up();
}

void UI::Parent::handle_mouse_down()
{
	for (auto* element : _children)
	{
		if (element->state.hovered)
			element->handle_mouse_down();
	}
	
	InteractiveElement::handle_mouse_down();
}

void UI::Parent::handle_mouse_enter()
{
	InteractiveElement::handle_mouse_enter();
}

void UI::Parent::handle_mouse_leave()
{
	for (auto* element : _children)
	{
		element->handle_mouse_leave();
	}
	
	InteractiveElement::handle_mouse_leave();
}

void UI::Parent::handle_mouse_move(MoveEvent event)
{
	bool e_handled = false;

	for (auto i = _children.count(); i --> 0;)
	{
		auto* element = (UI::InteractiveElement*)_children[i];
		
		if (
			e_handled == false &&
			element->styles.display != ElementStyles::DisplayType::none &&
			element->point_belongs(event.absolute)
			)
		{
			if (element->state.hovered == false)
			{
				element->handle_mouse_enter();
			}
			element->handle_mouse_move(event);
			e_handled = true;
		}
		else if (element->state.hovered == true)
		{
			element->handle_mouse_leave();
		}
	}

	InteractiveElement::handle_mouse_move(event);
}

void UI::Parent::handle_mouse_scroll(int delta)
{

	for (auto* element : _children)
	{
		if (element->state.hovered)
			element->handle_mouse_scroll(delta);
	}

	InteractiveElement::handle_mouse_scroll(delta);
}

void UI::Parent::handle_db_click()
{
	for (auto* element : _children)
	{
		if (element->state.hovered == true)
			element->handle_db_click();
	}
}

UI::ChildrenCollection* UI::Parent::children()
{
	return &this->_children;
}

UI::Parent::Parent( Position2 position)
	: _offset_position(position)
{}

void UI::Parent::draw(Render::DrawEvent2D* event)
{
	for (auto* element : _children)
	{
		if (element->styles.display != ElementStyles::DisplayType::none)
			element->draw(event);
	}
}

void UI::Parent::move_by(Position2 pos)
{
	for (auto* element : _children)
	{
		element->move_by(pos);
	}
}

 UI::InteractiveElement* UI::Parent::element_at(UINT index)
{
	return this->_children[index];
}

UI::Parent* UI::Parent::add_element(InteractiveElement* element)
{
	if (element->have_parent())
		return this;

	element->set_parent(this);
	element->move_by(this->get_position());
	children()->append(element);

	update_items();

	return this;
}

UI::Parent* UI::Parent::add_element(InteractiveElement* element, bool visible)
{
	element->styles.display = visible ? ElementStyles::DisplayType::none : ElementStyles::DisplayType::block;
	return this->add_element(element);
}

