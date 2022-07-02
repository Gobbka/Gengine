#pragma once
#include "DrawData.h"
#include "Vertex2D.h"

struct Css;

namespace Render {

	struct EventDrawCmd
	{
		UI::Vertex2D* vertices;
		unsigned* indices;
	};

	class CanvasDrawEvent
	{
		Canvas::DrawData* _draw_data;
		StencilUsage _stencil_mode = StencilUsage::ignore;
		short _stencil_layer = -1;
	public:
		CanvasDrawEvent(Canvas::DrawData* data);

		EventDrawCmd newDrawCmd(UINT vertices,UINT indices, GETexture*texture = nullptr) const;

		void drawRect(Position2 pos, Surface resolution, Color3XM color) const;
		void drawRect(Position2 pos, Surface resolution, GETexture* texture) const;
		void drawRect(Position2 pos, Surface resolution, Css* styles) const;

		StencilUsage stencil(StencilUsage mode);
		void stencilEnd(StencilUsage mode);
	};

	class DrawEvent2D final : public CanvasDrawEvent{

		GEGraphics* _context;
	public:
		DrawEvent2D(GEGraphics*ctx,Canvas::DrawData*data);

		void set_alpha(float alpha) const;
	};
}
