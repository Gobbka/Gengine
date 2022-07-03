#pragma once
#include <functional>
#include <vector>
#include "Events/MouseEvent.h"
#include "Canvas/BatchRenderer.h"
#include "Events/InteractionEventHandler.h"

namespace UI {
	class Parent;

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
		static void foreachAll(Parent* parent, std::function<void(InteractiveElement* element)>callback);
	public:
		void foreach(std::function<void(InteractiveElement* element)>callback) const;
		void foreachAll(std::function<void(InteractiveElement* element)>callback) const;
		void dragMove(InteractiveElement* element);
		void freeDragMove();

		bool hasElement(InteractiveElement* element) const;
		InteractiveForm* addElement(InteractiveElement* element);
	public:
		InteractiveForm(Render::GEGraphics* gfx,Position2* cursor_position);
		//InteractiveForm(InteractiveForm&& other) noexcept;
		~InteractiveForm() = default;
	public:
		EventStatus onMouseUp(MouseEvent* event);
		EventStatus onMouseDown(MouseEvent* event) const;
		EventStatus onMouseMove(MouseEvent* move_event) const;
		EventStatus onMouseScroll(MouseEvent* direction) const;
		EventStatus onDbClick() const;

		bool hidden() const;
		void show();
		void hide();

		void render();
	};
}
