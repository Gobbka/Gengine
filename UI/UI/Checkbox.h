#pragma once
#include "../IElement/InteractiveElement.h"

namespace UI
{
	class __declspec(dllexport) Checkbox final : public ::UI::InteractiveElement
	{
		void draw(Render::DrawEvent2D* event) override;

		bool* _lp_value;

		Position2 _position;
		Surface _resolution;
	public:
		Color3XM active_color{ 0.27f,0.73f,0.39f };
		Color3XM non_active_color{ 0.305f,0.305f,0.305f };
	
		bool is_checked() const;
		ElementDescription get_desc() override;

		Checkbox(Position2 position, Surface resolution, Color3XM color,bool*value);
		Checkbox(Position2 position, Surface resolution,bool*value);

		void set_position(Position2 position) override;

		Position2 get_position() override;

		Surface get_resolution() override;
		void set_resolution(Surface resolution) override;

		bool point_belongs(Position2 point) override;

		void move_by(Position2 offset) override;

		void handle_mouse_up() override;
		void set_texture(Render::Texture* texture) override;
	};
}

