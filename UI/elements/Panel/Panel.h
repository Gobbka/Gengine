#pragma once

#include "../IElement/Parentable.h"
#include "Canvas/Objects/Rectangle/Rectangle.h"


namespace Render {
	struct DrawEvent;
}

struct Position2;

namespace UI
{
	class Panel : public ::UI::Parent
	{
	protected:
		Canvas::Rectangle rect;

		void draw(Render::DrawEvent* event) override;
		void on_initialize() override;
	public:
		Application::UI::ElementDescription get_desc() override;

		Panel(Position2 position, Surface resolution, Color4 color);

		bool point_belongs(Position2 point) override;
		void set_pos(float x, float y) override;
		void set_color(Color4 color) override;

		void move_by(float x, float y) override;

		Position2 get_position() override;
		Surface get_resolution() override;
		Application::UI::InteractiveElement* set_resolution(float width, float height) override;
	};
}

