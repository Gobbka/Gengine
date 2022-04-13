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

		Render::GEDepthStencil _write_stencil;
		Render::GEDepthStencil _discard_stencil;
		Render::GEDepthStencil _ignore_stencil;
		Render::GEMaskEngine* _mask_engine;
	public:

		DrawData* begin();
		void present();

		CanvasImpl(Render::GEGraphics*context);
		CanvasImpl() = delete;
		~CanvasImpl() = default;

		Render::GEGraphics* gfx() const;
	};
}
