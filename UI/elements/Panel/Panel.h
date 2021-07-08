#pragma once

#include "../IElement/Parentable.h"
#include "Canvas/Objects/Rectangle/Rectangle.h"


namespace Render {
	struct DrawEvent;
}

struct Position2;

namespace UI
{
	class __declspec(dllexport) Panel : public Parent
	{
	protected:
		Canvas::Rectangle rect;

		void draw(Render::DrawEvent* event) override;
		void on_initialize() override;
	public:
		void init() override;
		Color4 get_color() override;
		
		ElementDescription get_desc() override;

		Panel(Position2 position, Surface resolution, Color4 color);

		bool point_belongs(Position2 point) override;
		void set_position(Position2 pos) override;
		void set_color(Color4 color) override;

		void move_by(Position2 pos) override;

		Position2 get_position() override;
		Surface get_resolution() override;
		void set_resolution(Surface surface) override;
		InteractiveElement* set_resolution(float width, float height) override;
	};
}

