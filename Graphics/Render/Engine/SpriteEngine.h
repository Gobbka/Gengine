#pragma once

namespace Core {
	class GraphicsContext;
}

namespace Render {
	class IGContext;
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
		IGContext* _context;
		Texture* _binded_texture[16]{};
	public:
		SpriteEngine(
			Core::GraphicsContext* context
		);

		void bind_texture(Texture* texture,unsigned slot);

		void begin_sprite_mode(bool light = false);
		void begin_color_mode();
	};
}
