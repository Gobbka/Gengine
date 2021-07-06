#pragma once
#include "../../../Canvas/elements/rectangle/rectangle.h"
#include "../IElement/InteractiveElement.h"


namespace Application
{
	namespace UI
	{
		class Checkbox : public InteractiveElement
		{
		private:
			void draw(Render::DrawEvent*event) override;

			bool checked = false;

			Canvas::Rectangle rectangle;
		public:
			Render::Color4 active_color { 0.27f,0.73f,0.39f };
			Render::Color4 non_active_color{ 0.305f,0.305f,0.305f };
		public:
			bool is_checked();
			ElementDescription get_desc() override;

			void on_initialize() override;
			
			EventCallback onChange = default_event_callback;

			Checkbox(Render::Position position,Render::Resolution resolution, Render::Color4 color);

			void set_pos(float x, float y) override;
			void set_color(Render::Color4 color) override;

			Render::Position get_position() override;

			Render::Resolution get_resolution() override;
			InteractiveElement* set_resolution(float width, float height) override;

			bool point_belongs(Render::Position point) override;

			void move_by(float x, float y) override;

			void handle_mouse_up() override;
		};
	}
}
