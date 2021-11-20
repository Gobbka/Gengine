#pragma once
#include <vector>

#include "InteractiveElement.h"

namespace Application {
	namespace Render {
		class Text;
	}
}

namespace UI
{

	class __declspec(dllexport) ChildrenCollection {
	protected:
		std::vector<UI::InteractiveElement*> _children;

	public:

		auto begin() { return _children.begin(); }
		auto end() { return _children.end(); }

		void foreach(std::function<void(InteractiveElement* element)> iterator);

		size_t count() const;

		UI::InteractiveElement* operator[](UINT index);

		InteractiveElement* last();

		void append(UI::InteractiveElement* child);

	};

	class __declspec(dllexport) Parent : public InteractiveElement
	{
		Position2 _offset_position;
		ChildrenCollection _children;
	protected:
		virtual void update_items() = 0;

		void handle_mouse_up() override;
		void handle_mouse_down() override;
		void handle_mouse_enter() override;
		void handle_mouse_leave() override;
		void handle_mouse_move(MoveEvent event) override;
		void handle_mouse_scroll(int delta) override;
		void handle_db_click() override;
	public:
		ChildrenCollection* children();

		Parent(Position2 position);

		void draw(Render::DrawEvent2D* event) override;
		void move_by(Position2 move) override;

		InteractiveElement* element_at(UINT index);

		Parent* add_element(InteractiveElement* element);
		Parent* add_element(InteractiveElement* element, bool visible);
	};
}
