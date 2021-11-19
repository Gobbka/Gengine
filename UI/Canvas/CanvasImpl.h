#pragma once
#include <vector>
#include "D11VertexAllocator.h"
#include "DrawData.h"

namespace Render
{
	template<typename T>
	class IVertexBuffer;
	class VertexShader;
	class PixelShader;
}

namespace Canvas {

	class CanvasImpl final {
		DrawData _drawData;
		Render::IVertexBuffer<UI::Vertex2D>* _buffer;
		Core::GraphicsContext* _context;
	public:

		DrawData* begin();
		void present();

		CanvasImpl(Core::GraphicsContext*context);
		CanvasImpl() = delete;
		~CanvasImpl() = default;

		Core::GraphicsContext* gfx();
	};
}
