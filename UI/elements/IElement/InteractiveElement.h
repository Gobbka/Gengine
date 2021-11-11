#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "functional"
#include "Canvas/Objects/IObject.h"
#include "Types/Types.h"


namespace Render {
	struct DrawEvent2D;
	struct DrawEvent;
}

namespace UI {
	class InteractiveForm;

	class Parent;
	class InteractiveElement;
	typedef InteractiveElement* UIElementEventArgs;

	enum class VisibleState : bool
	{
		visible = true,
		hidden = false,
	};

	struct ElementStyles
	{
		VisibleState      overflow = VisibleState::visible;
		enum class DisplayType
		{
			flex,
			block,
			none,
		} display = DisplayType::block;
		enum class FlexDirectionType
		{
			row,
			column,
		} flex_direction = FlexDirectionType::row;
		
		DirectX::XMFLOAT4 margin = { 0,0,0,0 };
	};

	struct ElementState
	{
		bool         hovered = false;
	};

	struct ElementDescription
	{
		// flags

		bool can_be_parent : 1;
		bool has_text : 1;

		// other

		const char* string_name;

		ElementDescription(bool can_be_parent, const char* string_name, bool has_text = false);
	};

	class __declspec(dllexport) InteractiveElement : public Canvas::IControllable
	{
	public:
		typedef std::function<void(UIElementEventArgs)> EventCallback;
	protected:
		// protected variables

		InteractiveForm* form = nullptr;
		Parent* parent = nullptr;
	protected:
		static void default_event_callback(UIElementEventArgs args) {}
	protected:
		float alpha = 1.f;
	public:
		// public variables

		UINT unique_id = 0;

		ElementStyles styles;
		ElementState  state;
	public:
		// public getters

		bool have_parent() const;

		// return's screen position
		Position2 get_position() override PURE;

		virtual ElementDescription get_desc() PURE;

		Surface get_resolution() override PURE;

		virtual bool point_belongs(Position2 point) PURE;

		// return's parent, if have
		Parent* get_parent() const;
		// return's form where this object where registered
		InteractiveForm* get_form() const;

		Position2 point_to(InteractiveElement* element);
	public:
		// public setters

		void set_parent(Parent* parent);

		void set_alpha(float alpha);

		void set_margin(float x, float y);
		void set_margin(float x, float y, float z, float w);
	public:
		// public voids
		void draw(Render::DrawEvent2D* event) override PURE;

		void initialize(InteractiveForm* form);
	protected:

	public:
		// public callbacks

		EventCallback onMouseEnter = default_event_callback;
		EventCallback onMouseLeave = default_event_callback;
		void(*onMouseMove)(UIElementEventArgs args, float mX, float mY) = [](UIElementEventArgs, float, float) {};
		std::function<void(UIElementEventArgs args, int delta)>onMouseScroll = [](UIElementEventArgs, int) {};
		EventCallback onMouseUp = default_event_callback;
		EventCallback onMouseDown = default_event_callback;
		EventCallback onDBClick = default_event_callback;


	public:
		//====================
		// EVENT HANDLER'S
		// if you wanna override something in your class,
		// u must to call base func if think that event need to be handled
		//

		virtual void handle_mouse_move(float mX, float mY);
		virtual void handle_mouse_leave();
		virtual void handle_mouse_enter();
		virtual void handle_mouse_up();
		virtual void handle_mouse_down();
		virtual void handle_db_click();
		virtual void handle_mouse_scroll(int delta);
	};
}
