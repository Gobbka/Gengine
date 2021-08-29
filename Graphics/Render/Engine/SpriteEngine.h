#pragma once
#include <d3d11.h>

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

		PixelShader*  _texture_ps;
		VertexShader* _texture_vs;

		PixelShader* _phong_ps;
		PixelShader*  _color_ps;

		ID3D11InputLayout* _inputLayout;

		PixelShader* _current_ps;

		bool _ps_active = true;
		
	public:
		SpriteEngine(
			Core::GraphicsContext* context,
			PixelShader* texture_ps,PixelShader*phong_ps,PixelShader*color_ps, VertexShader* texture_vs
		);

		void bind_texture(Texture* texture);

		void begin_sprite_mode(bool light = false);
		void begin_color_mode();

		bool set_ps_state(bool active);
	};
}
