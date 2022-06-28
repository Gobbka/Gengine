#pragma once
#include <functional>
#include <vector>
#include "Events/MouseEvent.h"
#include "Canvas/BatchRenderer.h"
#include "Events/InteractionEventHandler.h"

namespace UI {
	
	class InteractiveElement;

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

		Canvas::BatchRenderer _canvas;

		std::vector<InteractiveElement*> _children{};

		Position2* _cursor_position;
		DragStruct* _dragged = nullptr;
	public:
		void foreach(std::function<void(InteractiveElement* element)>callback) const;
		void dragMove(InteractiveElement* element);
		void freeDragMove();

		bool hasElement(InteractiveElement* element) const;
		InteractiveForm* addElement(InteractiveElement* element);
	public:
		InteractiveForm(Render::GEGraphics* pEngine,Position2*cursor_position);
		//InteractiveForm(InteractiveForm&& other) noexcept;
		~InteractiveForm() = default;
	public:
		EventStatus onMouseUp(MouseEvent* event);
		EventStatus onMouseDown(MouseEvent* event) const;
		EventStatus on_mouse_move(MouseEvent* move_event) const;
		EventStatus on_mouse_scroll(MouseEvent* direction) const;
		EventStatus on_db_click() const;

		bool hidden() const;
		void show();
		void hide();

		void render();
	};
}
