#pragma once
#include "../IElement/Parentable.h"
#include "../../Canvas/Objects/Rectangle/Rectangle.h"

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
		
		ElementDescription get_desc() override;

		Panel(Vector2 position, Surface resolution, Render::Texture*texture);

		bool point_belongs(Position2 point) override;
		void set_position(Position2 pos) override;

		void move_by(Position2 pos) override;

		void set_texture(Render::Texture* texture) override;

		Position2 get_position() override;
		Surface get_resolution() override;
		void set_resolution(Surface surface) override;
	};
}

