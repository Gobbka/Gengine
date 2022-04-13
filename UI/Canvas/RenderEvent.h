#pragma once
#include "DrawData.h"
#include "Vertex2D.h"

typedef unsigned UINT;
typedef unsigned char BYTE;

namespace Canvas
{
	class CanvasImpl;
	class IObject;
}

namespace Render {
	class MeshRenderer;
	class SpriteEngine;
	class Camera;

	struct EventDrawCmd
	{
		UI::Vertex2D* vertices;
		unsigned* indices;
	};

	class CanvasDrawEvent
	{
		Canvas::DrawData* _draw_data;
		StencilUsage _stencil_mode = StencilUsage::ignore;
		unsigned char _stencil_layer = 0;
	public:
		CanvasDrawEvent(Canvas::DrawData* data);

		EventDrawCmd new_draw_cmd(UINT vertices,UINT indices, GETexture*texture = nullptr) const;

		void draw_rect(Position2 pos,Surface resolution,Color3XM color) const;
		void draw_rect(Position2 pos,Surface resolution, GETexture* texture) const;

		StencilUsage stencil(StencilUsage mode);
		void stencil_end(StencilUsage mode);
	};

	class DrawEvent2D final : public CanvasDrawEvent{

		GEGraphics* _context;
	public:
		DrawEvent2D(GEGraphics*ctx,Canvas::DrawData*data);

		void set_alpha(float alpha) const;
	};
}
