#pragma once
#include "../IElement/Parentable.h"
#include "Rules/FlexRule.h"

namespace UI
{
	class __declspec(dllexport) FlexRowPanel : public Parent {
		Position2 _position;
		Surface _resolution;
		Render::GETexture* _texture;
		Color3XM _color;
		Vector2 _scroll_offset;
		FlexRule _location_rule;

		void update_items() override;
	public:

		void draw(Render::DrawEvent2D* event) override;

		ElementDescription get_desc() override;

		FlexRowPanel(Vector2 position, Surface resolution, Render::GETexture* texture);
		FlexRowPanel(Vector2 position, Surface resolution, Color3XM color);
		~FlexRowPanel() override;

		bool point_belongs(Position2 point) override;
		void set_position(Position2 pos) override;

		void move_by(Position2 pos) override;

		void set_texture(Render::GETexture* texture) override;

		Position2 get_position() override;
		Surface get_resolution() override;
		void set_resolution(Surface surface) override;

		void handle_mouse_scroll(MouseEvent* event) override;
	};
}
