#pragma once
#include "Css.h"
#include "ElementDescription.h"
#include "functional"
#include "Render/Common/Texture.h"
#include "Types/Types.h"

namespace Render {
	class DrawEvent2D;
}

namespace UI {
	class MouseEvent;

	class InteractiveForm;

	class Parent;
	class InteractiveElement;
	typedef InteractiveElement* UIElementEventArgs;

	class __declspec(dllexport) IControllable
	{
	public:
		virtual ~IControllable() = default;
		IControllable() = default;

		bool hidden = false;

		virtual void      set_position(Position2 pos) = 0;
		virtual Position2 get_position() = 0;

		virtual void    set_resolution(Surface surface) = 0;
		virtual Surface get_resolution() = 0;

		virtual void set_texture(Render::GETexture* texture) PURE;

		virtual void move_by(Position2) = 0;
	};

	struct ElementState
	{
		bool hovered = false;
	};

	class __declspec(dllexport) InteractiveElement : public IControllable
	{
	public:
		typedef std::function<void(MouseEvent*event)> EventCallback;
	protected:
		InteractiveForm* form = nullptr;
		Parent* parent = nullptr;

		static void default_event_callback(MouseEvent*event) {}
	public:
		UINT unique_id = 0;

		Css styles;
		ElementState  state;
	public:
		virtual void draw(Render::DrawEvent2D* event) = 0;

		// public getters

		bool haveParent() const;

		Position2 get_position() override PURE;

		virtual ElementDescription getDesc() PURE;

		Surface get_resolution() override PURE;

		virtual bool point_belongs(Position2 point) PURE;

		Parent* parentNode() const;
		InteractiveForm* get_form() const;
		Position2 point_to(InteractiveElement* element);
	public:
		// public setters
		void set_form(InteractiveForm* form);
		void set_parent(Parent* parent);

		void set_alpha(float alpha);

	public:
		// public callbacks

		EventCallback onMouseEnter = default_event_callback;
		EventCallback onMouseLeave = default_event_callback;
		EventCallback onMouseMove = default_event_callback;
		EventCallback onMouseScroll = default_event_callback;
		EventCallback onMouseUp = default_event_callback;
		EventCallback onMouseDown = default_event_callback;
		EventCallback onDBClick = default_event_callback;
	public:
		//====================
		// EVENT HANDLER'S
		// if you wanna override something in your class,
		// u must to call base func if think that event need to be handled
		//

		virtual void handleMouseMove(MouseEvent* event);
		virtual void handleMouseLeave();
		virtual void handleMouseEnter();
		virtual void handleMouseUp(MouseEvent* event);
		virtual void handleMouseDown(MouseEvent* event);
		virtual void handle_db_click();
		virtual void handle_mouse_scroll(MouseEvent* delta);
	};
}
