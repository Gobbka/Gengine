#pragma once
#include "../IElement/Parentable.h"
#include "Render/Common/Texture.h"

namespace Render {
	class DrawEvent2D;
}

namespace UI
{
	class __declspec(dllexport) Panel : public InteractiveElement
	{
		Position2 _position;
		Surface _resolution;
		Render::GETexture* _texture;
		Color3XM _color;

	public:

		void draw(Render::DrawEvent2D* event) override;


		ElementDescription getDesc() override;

		Panel(Vector2 position, Surface resolution, Render::GETexture*texture);
		Panel(Vector2 position, Surface resolution, Color3XM color);

		bool pointBelongs(Position2 point) override;
		void setPosition(Position2 pos) override;

		void moveBy(Position2 pos) override;

		void set_texture(Render::GETexture* texture) override;

		Position2 getPosition() override;
		Surface get_resolution() override;
		void set_resolution(Surface surface) override;
	};
}

