#pragma once
#include "Text.h"
#include "../IElement/InteractiveElement.h"

namespace UI
{
	class __declspec(dllexport) Button final : public InteractiveElement
	{
	
		Position2 _position;
		Surface _resolution;
		Color3XM _color;
		Color3XM _visible_color;
		Text _text;

		void draw(Render::DrawEvent2D* event) override;
	public:

		ElementDescription getDesc() override;

		Button(Position2 position, Surface resolution, Color3XM color,Render::SpriteFont*font, const wchar_t* text);

		bool point_belongs(Position2 point) override;

		void set_position(Position2 position) override;
		void set_color(Color3XM color);
		void set_text_color(Color3XM color);
		void move_by(Position2 offset) override;
		void set_resolution(Surface resolution) override;

		Surface get_resolution() override;
		Position2 get_position() override;

		EventCallback onClick = default_event_callback;

		void handleMouseUp(MouseEvent* event) override;
		void handleMouseDown(MouseEvent* event) override;
		void handle_mouse_enter() override;
		void handle_mouse_leave() override;
		void set_texture(Render::GETexture* texture) override;
	};
}

