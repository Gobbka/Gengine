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

	class __declspec(dllexport) IControllable
	{
	public:
		virtual ~IControllable() = default;
		IControllable() = default;

		bool hidden = false;

		virtual void      setPosition(Position2 pos) = 0;
		virtual Position2 getPosition() = 0;

		virtual void    set_resolution(Surface surface) = 0;
		virtual Surface get_resolution() = 0;

		virtual void set_texture(Render::GETexture* texture) PURE;

		virtual void moveBy(Position2) = 0;
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

		static void defaultEventCallback(MouseEvent*event) {}
	public:
		UINT unique_id = 0;

		Css styles;
		ElementState state;

		virtual void draw(Render::DrawEvent2D* event) = 0;

		bool haveParent() const;

		Position2 getPosition() override PURE;

		virtual ElementDescription getDesc() PURE;

		Surface get_resolution() override PURE;

		virtual bool pointBelongs(Position2 point) PURE;

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

		EventCallback onMouseEnter = defaultEventCallback;
		EventCallback onMouseLeave = defaultEventCallback;
		EventCallback onMouseMove = defaultEventCallback;
		EventCallback onMouseScroll = defaultEventCallback;
		EventCallback onMouseUp = defaultEventCallback;
		EventCallback onMouseDown = defaultEventCallback;
		EventCallback onDBClick = defaultEventCallback;
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
