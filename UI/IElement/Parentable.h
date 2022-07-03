#pragma once
#include <vector>

#include "InteractiveElement.h"

namespace UI
{
	class __declspec(dllexport) ChildrenCollection {
	protected:
		std::vector<InteractiveElement*> _children;

	public:

		auto begin() { return _children.begin(); }
		auto end() { return _children.end(); }

		void foreach(std::function<void(InteractiveElement* element)> iterator) const;

		size_t count() const;

		InteractiveElement* operator[](UINT index);

		InteractiveElement* last();

		void append(InteractiveElement* child);

	};

	class __declspec(dllexport) Parent : public InteractiveElement
	{
		Position2 _offset_position;
		ChildrenCollection _children;
	protected:
		virtual void update_items() = 0;

		void handleMouseUp(MouseEvent*event) override;
		void handleMouseDown(MouseEvent*event) override;
		void handleMouseEnter() override;
		void handleMouseLeave() override;
		void handleMouseMove(MouseEvent* event) override;
		void handle_mouse_scroll(MouseEvent* delta) override;
		void handle_db_click() override;
	public:
		ChildrenCollection* children();

		Parent(Position2 position);

		void draw(Render::DrawEvent2D* event) override;
		void moveBy(Position2 move) override;
		void setPosition(Position2 pos) override;

		InteractiveElement* element_at(UINT index);

		Parent* add_element(InteractiveElement* element);
		Parent* add_element(InteractiveElement* element, bool visible);
	};
}
