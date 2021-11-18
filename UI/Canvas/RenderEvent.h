#pragma once

typedef unsigned UINT;
typedef unsigned char BYTE;

namespace Core {
	class GraphicsContext;
}

namespace Canvas
{
	class Canvas;
	class IObject;
}

namespace Render {
	class MeshRenderer;
	class SpriteEngine;
	class Camera;

	struct __declspec(dllexport) DrawEvent2D {
	protected:
		Camera* _camera;
		Core::GraphicsContext* _context;
		SpriteEngine* _spriteEngine;
	private:
		UINT _stencil_layer = 0u;
		
	public:
		
		DrawEvent2D(Camera* camera, Canvas::Canvas* layer);

	private:
		UINT _draw_index = 0u;
	public:
		Canvas::Canvas* layer;

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
