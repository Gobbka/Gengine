#pragma once
#include "../IObject.h"

namespace Render {
	struct DrawEvent2D;
}

namespace Canvas
{
	class __declspec(dllexport) Rectangle final : public Canvas::IObject
	{
	public:
		INDEX size() override;
	private:
		Color4XM _background_color;
		Render::Texture* _background_texture;
		
		Position2 _position;
		Surface _resolution;

	private:
		void apply_rectangle() const;
		void apply_color();
		
		void on_initialize() override;
	public:
		Rectangle(Color4XM background,Position2 position,Surface resolution);
		
		void draw(Render::DrawEvent2D*draw_event) override;
		void set_position(Position2 pos) override;
		Position2 get_position() override;
		void set_resolution(Surface surface) override;
		Surface get_resolution() override;
		void move_by(Position2) override;
		void set_color(Color4XM color) override;
		Color4XM get_color() override;

		void set_texture(Render::Texture* texture) override;
	};
}
