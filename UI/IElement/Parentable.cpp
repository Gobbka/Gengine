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


void UI::Parent::handleMouseUp(MouseEvent* event)
{
	for(auto*element:_children)
	{
		if (element->state.hovered)
			element->handleMouseUp(event);
	}
	
	InteractiveElement::handleMouseUp(event);
}

void UI::Parent::handleMouseDown(MouseEvent* event)
{
	for (auto* element : _children)
	{
		if (element->state.hovered)
			element->handleMouseDown(event);
	}
	
	InteractiveElement::handleMouseDown(event);
}

void UI::Parent::handleMouseEnter()
{
	InteractiveElement::handleMouseEnter();
}

void UI::Parent::handleMouseLeave()
{
	for (auto* element : _children)
	{
		element->handleMouseLeave();
	}
	
	InteractiveElement::handleMouseLeave();
}

void UI::Parent::handleMouseMove(MouseEvent* event)
{
	bool e_handled = false;

	for (auto i = _children.count(); i --> 0;)
	{
		auto* element = _children[i];
		
		if (
			e_handled == false &&
			element->styles.display != Css::Display::none &&
			element->pointBelongs(event->screen)
			)
		{
			if (element->state.hovered == false)
			{
				element->handleMouseEnter();
			}
			element->handleMouseMove(event);
			e_handled = true;
		}
		else if (element->state.hovered == true)
		{
			element->handleMouseLeave();
		}
	}

	InteractiveElement::handleMouseMove(event);
}

void UI::Parent::handle_mouse_scroll(MouseEvent* delta)
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
		if (element->styles.display != Css::Display::none)
			element->draw(event);
	}
}

void UI::Parent::moveBy(Position2 pos)
{
	for (auto* element : _children)
	{
		element->moveBy(pos);
	}
}

void UI::Parent::setPosition(Position2 pos)
{
	for (auto* element : _children)
	{
		element->setPosition(pos);
	}
}

UI::InteractiveElement* UI::Parent::element_at(UINT index)
{
	return this->_children[index];
}

UI::Parent* UI::Parent::add_element(InteractiveElement* element)
{
	if (element->haveParent())
		return this;

	element->set_parent(this);
	element->moveBy(this->getPosition());
	children()->append(element);

	update_items();

	return this;
}

UI::Parent* UI::Parent::add_element(InteractiveElement* element, bool visible)
{
	element->styles.display = visible ? Css::Display::none : Css::Display::block;
	return this->add_element(element);
}

