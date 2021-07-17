#pragma once
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
		Core::GraphicsContext* _graphicsContext;

		PixelShader* _texture_ps;
		VertexShader* _texture_vs;
		
		ID3D11InputLayout* _layout;

		ID3D11VertexShader* _old_vs = nullptr;
		ID3D11PixelShader* _old_ps  = nullptr;
		ID3D11InputLayout* _old_layout = nullptr;
	public:
		SpriteEngine(Core::GraphicsContext* context,PixelShader*ps,VertexShader*vs, ID3D11InputLayout* layout);
		
		void begin();
		void end();
	};
}
