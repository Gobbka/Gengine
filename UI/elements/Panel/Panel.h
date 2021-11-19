#pragma once
#include "../IElement/Parentable.h"

namespace Render {
	struct DrawEvent2D;
	struct DrawEvent;
}

namespace UI
{
	class __declspec(dllexport) Panel : public Parent
	{
		Position2 _position;
		Surface _resolution;
		Render::Texture* _texture;
		Color3XM _color;

	public:

		void draw(Render::DrawEvent2D* event) override;


		ElementDescription get_desc() override;

		Panel(Vector2 position, Surface resolution, Render::Texture*texture);
		Panel(Vector2 position, Surface resolution, Color3XM color);

		bool point_belongs(Position2 point) override;
		void set_position(Position2 pos) override;

		void move_by(Position2 pos) override;

		void set_texture(Render::Texture* texture) override;

		Position2 get_position() override;
		Surface get_resolution() override;
		void set_resolution(Surface surface) override;
	};
}

