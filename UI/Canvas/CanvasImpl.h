#pragma once
#include "DrawData.h"

namespace Core
{
	class DX11Graphics;
}

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
		Core::DX11Graphics* _context;
	public:

		DrawData* begin();
		void present();

		CanvasImpl(Core::DX11Graphics*context);
		CanvasImpl() = delete;
		~CanvasImpl() = default;

		Core::DX11Graphics* gfx() const;
	};
}
