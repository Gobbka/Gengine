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

	class ReadChildrenCollection {
	protected:
		std::vector<UI::InteractiveElement*> _children;

	public:
		void foreach(std::function<void(InteractiveElement* element)> iterator);

		size_t count();

		UI::InteractiveElement* operator[](UINT index);

		InteractiveElement* last();
	};

	class ReadWriteChildrenCollection : public ReadChildrenCollection {
	public:
		void append(UI::InteractiveElement* child);
	};

	class __declspec(dllexport) Parent : public InteractiveElement
	{
	private:
		Position2 _offset_position;
		ReadWriteChildrenCollection _children;
		bool initialized = false;
	protected:
		void handle_mouse_up() override;
		void handle_mouse_down() override;
		void handle_mouse_enter() override;
		void handle_mouse_leave() override;
		void handle_mouse_move(float mX, float mY) override;
		void handle_mouse_scroll(int delta) override;
		void handle_db_click() override;

		void on_initialize() override;
	public:
		ReadChildrenCollection* children();

		Parent(Position2 position);

		void draw(::Render::DrawEvent* event) override;
		void set_color(Color4 color) override;
		void move_by(Position2 move) override;

		InteractiveElement* element_at(UINT index);

		virtual Parent* add_element(InteractiveElement* element);
		Parent* add_element(InteractiveElement* element, bool visible);
	};
}
