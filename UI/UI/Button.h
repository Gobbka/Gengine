#pragma once
#include "Text.h"
#include "../IElement/InteractiveElement.h"

namespace UI
{
	class __declspec(dllexport) Button final : public InteractiveElement
	{
	
		Position2 _position;
		Surface _resolution;
		Color3XM _color;
		Color3XM _visible_color;
		Text _text;

		void draw(Render::DrawEvent2D* event) override;
	public:

		ElementDescription getDesc() override;

		Button(Position2 position, Surface resolution, Color3XM color,Render::SpriteFont*font, const wchar_t* text);

		bool pointBelongs(Position2 point) override;

		void setPosition(Position2 position) override;
		void set_color(Color3XM color);
		void set_text_color(Color3XM color);
		void moveBy(Position2 offset) override;
		void set_resolution(Surface resolution) override;

		Surface get_resolution() override;
		Position2 getPosition() override;

		EventCallback onClick = defaultEventCallback;

		void handleMouseUp(MouseEvent* event) override;
		void handleMouseDown(MouseEvent* event) override;
		void handleMouseEnter() override;
		void handleMouseLeave() override;
		void set_texture(Render::GETexture* texture) override;
	};
}

