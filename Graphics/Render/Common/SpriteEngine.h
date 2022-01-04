#pragma once
#include "Texture.h"

namespace Core {
	class DX11Graphics;
}

namespace Render {
	class IGContext;
	class PixelShader;
	class VertexShader;

	class __declspec(dllexport) SpriteEngine
	{
	private:
		enum class DrawMode
		{
			none,
			sprite,
			color,
		};
		
	private:
		Core::DX11Graphics* _graphicsContext;
		IGContext* _context;
		GETexture* _binded_texture[16]{};
	public:
		SpriteEngine(
			Core::DX11Graphics* context
		);

		void bind_texture(GETexture* texture,unsigned slot);

		void begin_sprite_mode(bool light = false);
		void begin_color_mode();
	};
}
