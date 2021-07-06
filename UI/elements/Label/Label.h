#pragma once
#include "SpriteFont.h"
#include "../../../../Render/Text/Text.h"
#include "../IElement/InteractiveElement.h"

namespace Application
{
	namespace UI
	{

		class Label : public InteractiveElement, public Render::Text
		{
		private:
			Render::Position position;
		public:
			
			bool scalable = false;
			
			void draw(Render::DrawEvent* event) override;
			
			Label(Render::Position position, const char* text,DirectX::SpriteFont*font, Render::Color4 color);
			Label(Render::Position position, const char* text,DirectX::SpriteFont*font, Render::Color4 color, Render::Resolution limitResolution);

			InteractiveElement* set_resolution(float width, float height) override;
			InteractiveElement* set_resolution(Render::Resolution resolution);
			
			void set_pos(float x, float y) override;
			void set_color(Render::Color4 color) override;
			void move_by(float x, float y) override;

			bool point_belongs(Render::Position point) override;
			
			Render::Position   get_position() override;
			Render::Resolution get_resolution() override;
			ElementDescription get_desc() override;
		};
	}

}