#include "Parentable.h"
#include "../../InteractiveForm.h"
#include <iostream>

void UI::ReadChildrenCollection::foreach(std::function<void(UI::InteractiveElement* element)> iterator)
{
	for(auto*element: _children)
		iterator(element);
}

void UI::ReadWriteChildrenCollection::append(UI::InteractiveElement* child)
{
	_children.push_back(child);
}

size_t UI::ReadChildrenCollection::count() const
{
	return _children.size();
}

UI::InteractiveElement* UI::ReadChildrenCollection::operator[](UINT index)
{
	return _children[index];
}

UI::InteractiveElement* UI::ReadChildrenCollection::last()
{
	auto _size = count();
	if (count() == 0)
		return nullptr;
	
	return _children[_size - 1];
}


void UI::Parent::handle_mouse_up()
{
	_children.foreach([&](UI::InteractiveElement* element) {
		if (element->state.hovered)
			element->handle_mouse_up();
	});
	
	InteractiveElement::handle_mouse_up();
}

void UI::Parent::handle_mouse_down()
{
	_children.foreach([&](UI::InteractiveElement* element) {
		if (element->state.hovered)
			element->handle_mouse_down();
	});
	
	InteractiveElement::handle_mouse_down();
}

void UI::Parent::handle_mouse_enter()
{
	InteractiveElement::handle_mouse_enter();
}

void UI::Parent::handle_mouse_leave()
{
	_children.foreach([&](UI::InteractiveElement* element) {
		element->handle_mouse_leave();
	});
	
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
	this->_children.foreach([&](UI::InteractiveElement* element) {
		if (element->state.hovered)
			element->handle_mouse_scroll(delta);
	});
	
	InteractiveElement::handle_mouse_scroll(delta);
}

void UI::Parent::handle_db_click()
{
	this->_children.foreach([](UI::InteractiveElement* element)
		{
			if (element->state.hovered == true)
				element->handle_db_click();
		});
}

UI::ReadChildrenCollection* UI::Parent::children()
{
	return &this->_children;
}

UI::Parent::Parent( Position2 position)
	: _offset_position(position)
{}

void UI::Parent::draw(Render::DrawEvent2D* event)
{
	this->_children.foreach([&](UI::InteractiveElement* element) {
		if (element->styles.display != ElementStyles::DisplayType::none)
			element->draw(event);
	});
}

void UI::Parent::move_by(Position2 pos)
{
	this->_children.foreach([&](UI::InteractiveElement* element) {
		element->move_by(pos);
	});
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
	
	auto* last_element = _children.last();
	this->_children.append(element);

	if (last_element != nullptr)
	{
		auto relative_point = last_element->point_to(this);
		auto element_res = last_element->get_resolution();

		if (this->styles.display == ElementStyles::DisplayType::block)
		{
			std::cout << relative_point.y << '\n';
			element->move_by({ 0,relative_point.y - element_res.height });
		}

		if(this->styles.display == ElementStyles::DisplayType::flex)
		{
			if(
				relative_point.x + element_res.width + 
				element->styles.margin.w + element->styles.margin.y +
				element->get_resolution().width > get_resolution().width
				)
			{
				element->move_by({ 0,relative_point.y - element_res.height });
			}else
			{
				element->move_by({ relative_point.x + element_res.width,relative_point.y });
			}	
		}
	}
	
	return this;
}

UI::Parent* UI::Parent::add_element(InteractiveElement* element, bool visible)
{
	element->styles.display = visible ? ElementStyles::DisplayType::none : ElementStyles::DisplayType::block;
	return this->add_element(element);
}

