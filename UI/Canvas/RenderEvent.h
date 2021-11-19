#pragma once
#include "DrawData.h"
#include "Vertex2D.h"

typedef unsigned UINT;
typedef unsigned char BYTE;

namespace Core {
	class GraphicsContext;
}

namespace Canvas
{
	class CanvasImpl;
	class IObject;
}

namespace Render {
	class MaskEngine;
	class MeshRenderer;
	class SpriteEngine;
	class Camera;

	class CanvasDrawEvent
	{
		Canvas::DrawData* _draw_data;
	public:
		CanvasDrawEvent(Canvas::DrawData* data);

		UI::Vertex2D* new_draw_cmd(UINT size,Texture*texture = nullptr) const;

		void draw_rect(Position2 pos,Surface resolution,Color3XM color) const;
		void draw_rect(Position2 pos,Surface resolution,Texture* texture) const;
	};

	class DrawEvent2D final : public CanvasDrawEvent{

		Core::GraphicsContext* _context;
		UINT _stencil_layer = 0u;
	public:
		DrawEvent2D(Core::GraphicsContext*ctx,Canvas::DrawData*data);

		void mask_draw_begin() const;
		void mask_discard_begin(bool increase_layer = true);
		void mask_discard_end(bool decrease_layer = true);
		void mask_set_stencil(BYTE new_index);
		BYTE mask_get_stencil_layer() const;

		void set_alpha(float alpha) const;
	};
}
