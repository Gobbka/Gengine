#pragma once
#include "../IElement/Parentable.h"
#include "Rules/FlexRule.h"

namespace UI {
	class __declspec(dllexport) FlexColumnPanel : public Parent
	{
		Position2 _position;
		Surface _resolution;
		Render::GETexture* _texture;
		Color3XM _color;
		FlexRule _location_rule;

		void update_items() override;
	public:
		void draw(Render::DrawEvent2D* event) override;

		ElementDescription getDesc() override;

		FlexColumnPanel(Vector2 position, Surface resolution, Render::GETexture* texture);
		FlexColumnPanel(Vector2 position, Surface resolution, Color3XM color);

		bool pointBelongs(Position2 point) override;
		void setPosition(Position2 pos) override;

		void moveBy(Position2 pos) override;

		void set_texture(Render::GETexture* texture) override;

		Position2 getPosition() override;
		Surface get_resolution() override;
		void set_resolution(Surface surface) override;
	};
}
