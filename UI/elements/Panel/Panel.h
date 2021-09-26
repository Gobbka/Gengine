#pragma once

#include "../IElement/Parentable.h"
#include "Canvas/Objects/Rectangle/Rectangle.h"


namespace Render {
	struct DrawEvent2D;
	struct DrawEvent;
}

namespace UI
{
	class __declspec(dllexport) Panel : public Parent
	{
	protected:
		Canvas::Rectangle rect;

		void draw(Render::DrawEvent2D* event) override;
		void on_initialize() override;
	public:
		Color4XM get_color() override;
		
		ElementDescription get_desc() override;

		Panel(Vector2 position, Surface resolution, Color4XM color);

		bool point_belongs(Position2 point) override;
		void set_position(Position2 pos) override;
		void set_color(Color4XM color) override;

		void move_by(Position2 pos) override;
		void scale(float value) override;

		void set_texture(Render::Texture* texture) override;

		Position2 get_position() override;
		Surface get_resolution() override;
		void set_resolution(Surface surface) override;
	};
}

