#pragma once
#include "../IElement/InteractiveElement.h"

namespace Render
{
	struct SpriteFont;
}

namespace Core
{
	class GraphicsContext;
}

namespace UI
{
	struct Vertex2D;

	struct __declspec(dllexport) Text final : public InteractiveElement
	{
	private:
		unsigned _length;
		const wchar_t* _text;
		Vertex2D* _vbuffer;
		unsigned* _ibuffer;

		Position2 _position;
	public:
		Render::SpriteFont* font;

		Text(Render::SpriteFont* font,const wchar_t*text,Position2 pos);
		Text(Text&& other) noexcept;
		Text& operator=(Text&& other) noexcept;
		~Text() override;

		void set_text(const wchar_t* text);

		void set_position(Position2 pos) override;
		void set_resolution(Surface surface) override;
		void set_texture(Render::Texture* texture) override;
		void move_by(Position2) override;
		void draw(Render::DrawEvent2D* event) override;
		void set_color(Color3XM color);
		Position2 get_position() override;
		ElementDescription get_desc() override;
		Surface get_resolution() override;
		bool point_belongs(Position2 point) override;
	};
}
