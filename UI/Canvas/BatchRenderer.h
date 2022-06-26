#pragma once
#include <Render/Common/VBuffer.h>

#include "DrawData.h"

namespace Canvas {

	class BatchRenderer final {
		DrawData _drawData;
		Render::GEVBuffer<UI::Vertex2D>* _buffer;
		Render::GEIndexBuffer* _ibuffer;
		Render::GEGraphics* _context;

		Render::GEDepthStencil _write_stencil;
		Render::GEDepthStencil _discard_stencil;
		Render::GEDepthStencil _ignore_stencil;
		Render::GEMaskEngine* _mask_engine;
	public:

		DrawData* begin();
		void present();

		BatchRenderer(Render::GEGraphics*context);
		BatchRenderer() = delete;
		~BatchRenderer() = default;

		Render::GEGraphics* gfx() const;
	};
}
