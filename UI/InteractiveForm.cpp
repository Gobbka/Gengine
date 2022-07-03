#include "InteractiveForm.h"

#include <iostream>

#include "IElement/InteractiveElement.h"
#include "Canvas/RenderEvent.h"
#include "IElement/Parentable.h"

using namespace UI;

void InteractiveForm::foreachAll(Parent* parent, std::function<void(InteractiveElement* element)> callback)
{
	auto& children = *parent->children();
	for(auto* element : children)
	{
		callback(element);

		const auto description = element->getDesc();
		if (description.can_be_parent)
		{
			foreachAll((Parent*)element, callback);
		}
	}
}

void InteractiveForm::foreach(std::function<void(InteractiveElement* element)> callback) const
{
	for(auto* element : _children)
	{
		callback(element);
	}
}

void InteractiveForm::foreachAll(std::function<void(InteractiveElement* element)> callback) const
{
	for(auto* element : _children)
	{
		callback(element);

		const auto description = element->getDesc();
		if(description.can_be_parent)
		{
			foreachAll((Parent*)element, callback);
		}
	}
}

void InteractiveForm::dragMove(InteractiveElement* element)
{
	auto pos = element->getPosition();
	auto cursor = *_cursor_position;

	pos.y *= -1;
	cursor -= pos;
	_dragged = new DragStruct{ cursor ,element};
}

void InteractiveForm::freeDragMove()
{
	if (_dragged == nullptr) return;

	delete _dragged;
	_dragged = nullptr;
}

bool InteractiveForm::hasElement(InteractiveElement* element) const
{
	for (auto* in_element : _children)
		if (element == in_element)
			return true;
	return false;
}


InteractiveForm* InteractiveForm::addElement(InteractiveElement* element)
{
	element->set_form(this);
	_children.push_back(element);

	return this;
}

InteractiveForm::InteractiveForm(Render::GEGraphics* gfx, Position2* cursor_position)
	: _hidden(false)
	, _canvas(gfx)
	, _cursor_position(cursor_position)
{}

EventStatus InteractiveForm::onMouseMove(MouseEvent* move_event) const
{
	if (hidden())
	{
		return EventStatus::none;
	}

	if (_dragged)
	{
		const auto new_pos = _dragged->element->getPosition() + move_event->delta;
		_dragged->element->setPosition(new_pos);
		return EventStatus::handled;
	}

	std::vector<InteractiveElement*> event_objects;

	foreachAll([&](InteractiveElement* element)
	{
		if(element->styles.display != Css::Display::none && element->pointBelongs(move_event->screen))
		{
			event_objects.push_back(element);
			return;
		}

		if (element->state.hovered)
		{
			element->handleMouseLeave();
		}
	});

	for(auto*element : event_objects)
	{
		if(!element->state.hovered)
		{
			element->handleMouseEnter();
		}
		if(element->styles.cursor == Css::Cursor::pointer)
		{
			SetCursor(LoadCursor(nullptr, IDC_HAND));
		}
		element->handleMouseMove(move_event);
	}

	return EventStatus::none;
}

EventStatus InteractiveForm::onMouseScroll(MouseEvent* direction) const
{
	if (hidden())
	{
		return EventStatus::none;
	}
	
	foreach([direction](InteractiveElement* element)
		{
			if (element->state.hovered == true)
			{
				element->handle_mouse_scroll(direction);
			}
		});
	return EventStatus::none;
}

EventStatus InteractiveForm::onDbClick() const
{
	if (hidden())
	{
		return EventStatus::none;
	}

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
		if (element->styles.display != Css::Display::none)
		{
			element->draw(&event);
		}
	}

	_canvas.present();
}

EventStatus InteractiveForm::onMouseUp(MouseEvent*event)
{
	if (hidden())
	{
		return EventStatus::none;
	}

	for(auto*element : _children)
	{
		if (element->state.hovered == true)
		{
			element->handleMouseUp(event);
		}
	}

	freeDragMove();

	return EventStatus::none;
}

EventStatus InteractiveForm::onMouseDown(MouseEvent* event) const
{
	if (hidden())
	{
		return EventStatus::none;
	}

	for(auto* element : _children)
	{
		if (element->state.hovered == true)
		{
			element->handleMouseDown(event);
		}
	}

	return EventStatus::none;
}

