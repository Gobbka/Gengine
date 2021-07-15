#pragma once
#include <functional>
#include <vector>

#include "Canvas/CanvasLayer.h"
#include "Graphics/Types.h"
#include "Events/InteractionEventHandler.h"

namespace Render {
	class Camera;
	struct DrawEvent;
}

namespace UI {
	struct InteractiveElementDesc;
	class InteractiveElement;

	class __declspec(dllexport) InteractiveForm final : public Canvas::Canvas2DLayer
	{
	public:
		struct DragStruct
		{
			Position2 dragged_offset;
			InteractiveElement* element;
		};
	private:
		std::vector<UI::InteractiveElement*> childs;
		void render_components(Render::DrawEvent* event) override;

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
		virtual ~InteractiveForm();
	public:
		Interaction::EventStatus on_lbmouse_up();
		Interaction::EventStatus on_lbmouse_down();
		Interaction::EventStatus on_mouse_move(int mx, int my);
		Interaction::EventStatus on_mouse_scroll(short direction);
	};
}
