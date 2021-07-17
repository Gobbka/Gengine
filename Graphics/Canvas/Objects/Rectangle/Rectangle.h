#pragma once
#include "../I2DCanvasObject.h"

namespace Canvas
{
	class __declspec(dllexport) Rectangle final : public Canvas::I2DCanvasObject
	{
	public:
		INDEX size() override;
	private:
		Color4 _background_color;
		Render::Texture* _background_texture;
		
		Position2 _position;
		Surface _resolution;

	private:
		void apply_rectangle();
		void apply_color();
		
		void on_initialize() override;
	public:
		Rectangle(Color4 background,Position2 position,Surface resolution);
		
		void draw(Render::DrawEvent*draw_event) override;
		void set_position(Position2 pos) override;
		Position2 get_position() override;
		void set_resolution(Surface surface) override;
		Surface get_resolution() override;
		void move_by(Position2) override;
		void set_color(Color4 color) override;
		Color4 get_color() override;

		void set_texture(Render::Texture* texture) override;
	};
}
