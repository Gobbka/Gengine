#pragma once

namespace Core {
	class GraphicsContext;
}

namespace Render {
	class Texture;
	class PixelShader;
	class VertexShader;

	class SpriteEngine
	{
	private:
		enum class DrawMode
		{
			none,
			sprite,
			color,
		};
		
	private:
		Core::GraphicsContext* _graphicsContext;
		Texture* _binded_texture;
	public:
		SpriteEngine(
			Core::GraphicsContext* context
		);

		void bind_texture(Texture* texture);

		void begin_sprite_mode(bool light = false);
		void begin_color_mode();
	};
}
