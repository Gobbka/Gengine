#pragma once

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class PixelShader;

	class PixelShaderLayout
	{
		Core::GraphicsContext* _context;
		PixelShader* _ps;
	public:
		PixelShaderLayout(Core::GraphicsContext* context);
		
		void bind(PixelShader*shader);
		void remove();
	};
}
