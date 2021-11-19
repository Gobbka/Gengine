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
	class MeshRenderer;
	class SpriteEngine;
	class Camera;

	class CanvasDrawEvent
	{
		Canvas::DrawData* _draw_data;
	public:
		CanvasDrawEvent(Canvas::DrawData* data);

		UI::Vertex2D* new_draw_cmd(UINT size) const;

		void draw_rect(Position2 pos,Surface resolution,Color3XM color) const;
	};

	struct __declspec(dllexport) DrawEvent2D final {
	
		Camera* _camera;
		Core::GraphicsContext* _context;
		SpriteEngine* _spriteEngine;
		UINT _stencil_layer = 0u;
		UINT _draw_index = 0u;
		
	public:
		
		DrawEvent2D(Camera* camera, Canvas::CanvasImpl* layer);

	private:
	public:
		Canvas::CanvasImpl* layer;

		UI::Vertex2D* draw(UINT vertices_count);
		void draw_vertex(UINT count, UINT start = 0) const;
		void draw_object(Canvas::IObject* object);

	public:
		SpriteEngine* sprite_engine() const;

		void mask_draw_begin() const;
		void mask_discard_begin(bool increase_layer = true);
		void mask_discard_end(bool decrease_layer = true);
		void mask_set_stencil(BYTE new_index);
		BYTE mask_get_stencil_layer() const;
		void mask_clear() const;

		void set_alpha(float alpha) const;
	};
}
