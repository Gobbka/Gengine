#pragma once
#include <d3d11.h>

namespace Canvas
{
	class I2DCanvasObject;
}

namespace Render {
	class D3DEngine;
	class ILayer;

	struct DrawEvent {
	private:
		D3DEngine* _engine;
		
		UINT _draw_index = 0u;
		
	public:
		ILayer* layer;

		DrawEvent(D3DEngine* engine , ILayer* layer);

	public:
		void draw_vertex(UINT count, UINT start = 0) const;
		void draw_object(Canvas::I2DCanvasObject*object);
	};
}
