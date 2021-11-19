#pragma once
#include "functional"
#include "Types/Types.h"

namespace Render {
	class DrawEvent2D;
	class Texture;
}

namespace UI {

	struct MoveEvent;
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

		virtual void set_texture(Render::Texture* texture) PURE;

		virtual void move_by(Position2) = 0;
	};


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
			block,
			none,
		} display = DisplayType::block;
		
		DirectX::XMFLOAT4 margin = { 0,0,0,0 };
	};

	struct ElementState
	{
		bool hovered = false;
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

	class __declspec(dllexport) InteractiveElement : public IControllable
	{
	public:
		typedef std::function<void(UIElementEventArgs)> EventCallback;
	protected:
		InteractiveForm* form = nullptr;
		Parent* parent = nullptr;
		float alpha = 1.f;

		static void default_event_callback(UIElementEventArgs args) {}
	public:
		UINT unique_id = 0;

		ElementStyles styles;
		ElementState  state;
	public:
		virtual void draw(Render::DrawEvent2D* event) = 0;

		// public getters

		bool have_parent() const;

		Position2 get_position() override PURE;

		virtual ElementDescription get_desc() PURE;

		Surface get_resolution() override PURE;

		virtual bool point_belongs(Position2 point) PURE;

		Parent* get_parent() const;
		InteractiveForm* get_form() const;
		Position2 point_to(InteractiveElement* element);
	public:
		// public setters
		void set_form(InteractiveForm* form);
		void set_parent(Parent* parent);

		void set_alpha(float alpha);

		void set_margin(float x, float y);
		void set_margin(float x, float y, float z, float w);

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

		virtual void handle_mouse_move(MoveEvent event);
		virtual void handle_mouse_leave();
		virtual void handle_mouse_enter();
		virtual void handle_mouse_up();
		virtual void handle_mouse_down();
		virtual void handle_db_click();
		virtual void handle_mouse_scroll(int delta);
	};
}
