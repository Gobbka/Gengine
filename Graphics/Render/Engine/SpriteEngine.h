﻿#pragma once
#include <d3d11.h>

namespace Core {
	class GraphicsContext;
}

namespace Render {
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

		PixelShader*  _texture_ps;
		VertexShader* _texture_vs;

		PixelShader*  _color_ps;
		VertexShader* _color_vs;
		
		ID3D11InputLayout* _texture_layout;
		ID3D11InputLayout* _color_layout;

		DrawMode _drawMode;
	public:
		SpriteEngine(
			Core::GraphicsContext* context,
			PixelShader* texture_ps, VertexShader* texture_vs, ID3D11InputLayout* texture_layout,
			PixelShader* color_ps, VertexShader* color_vs, ID3D11InputLayout* color_layout
		);

		void begin_sprite_mode();
		void begin_color_mode();
		void end();
		
	};
}
