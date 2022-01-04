#pragma once
#include "DrawData.h"

namespace Render
{
	template<typename T>
	class IVertexBuffer;
}

namespace Canvas {

	class CanvasImpl final {
		DrawData _drawData;
		Render::IVertexBuffer<UI::Vertex2D>* _buffer;
		Render::GEIndexBuffer* _ibuffer;
		Render::GEGraphics* _context;
	public:

		DrawData* begin();
		void present();

		CanvasImpl(Render::GEGraphics*context);
		CanvasImpl() = delete;
		~CanvasImpl() = default;

		Render::GEGraphics* gfx() const;
	};
}
