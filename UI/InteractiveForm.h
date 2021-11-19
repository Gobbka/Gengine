#pragma once
#include <functional>
#include <vector>

#include "Canvas/CanvasImpl.h"
#include "Events/InteractionEventHandler.h"

namespace Render {
	class Camera;
}

namespace UI {
	struct InteractiveElementDesc;
	class InteractiveElement;

	struct __declspec(dllexport) MoveEvent
	{
		Position2 delta;
		Position2 absolute;
	};

	class __declspec(dllexport) InteractiveForm final
	{
	public:
		struct DragStruct
		{
			Position2 dragged_offset;
			InteractiveElement* element;
		};
	private:
		bool _hidden;

		Canvas::CanvasImpl _canvas;

		std::vector<UI::InteractiveElement*> _childs;

		Position2* _cursor_position;
		DragStruct* dragged = nullptr;
	public:
		

		void foreach(std::function<void(UI::InteractiveElement* element)>callback);
		void drag_move(UI::InteractiveElement* element);
		void free_drag_move();

		bool has_element(UI::InteractiveElement* element);
		InteractiveForm* add_element(UI::InteractiveElement* element);
	public:
		InteractiveForm(Core::GraphicsContext* pEngine,Position2*cursor_position);
		//InteractiveForm(InteractiveForm&& other) noexcept;
		~InteractiveForm() = default;
	public:
		Interaction::EventStatus on_lbmouse_up();
		Interaction::EventStatus on_lbmouse_down();
		Interaction::EventStatus on_mouse_move(MoveEvent move_event);
		Interaction::EventStatus on_mouse_scroll(short direction);
		Interaction::EventStatus on_db_click();

		bool hidden() const;
		void show();
		void hide();

		void render();
	};
}
