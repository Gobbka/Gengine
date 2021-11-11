#pragma once
#include <functional>
#include <vector>

#include "Canvas/Canvas.h"
#include "Types/Types.h"
#include "Events/InteractionEventHandler.h"

namespace Render {
	class Camera;
}

namespace UI {
	struct InteractiveElementDesc;
	class InteractiveElement;

	class __declspec(dllexport) InteractiveForm final : public Canvas::Canvas
	{
	public:
		struct DragStruct
		{
			Position2 dragged_offset;
			InteractiveElement* element;
		};
	private:
		std::vector<UI::InteractiveElement*> _childs;
		void render_components(Render::DrawEvent2D* event) override;

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
		virtual ~InteractiveForm();
	public:
		Interaction::EventStatus on_lbmouse_up();
		Interaction::EventStatus on_lbmouse_down();
		Interaction::EventStatus on_mouse_move(int mx, int my);
		Interaction::EventStatus on_mouse_scroll(short direction);
		Interaction::EventStatus on_db_click();
	};
}
