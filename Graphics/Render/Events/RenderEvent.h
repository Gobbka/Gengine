#pragma once
#include <d3d11.h>

namespace Canvas
{
	class I2DCanvasObject;
}

namespace Render {
	class SpriteEngine;
	class Camera;
	class ILayer;

	struct __declspec(dllexport) DrawEvent {
	private:
		Camera* _engine;
		
		UINT _draw_index = 0u;
		UINT _stencil_layer = 0u;
		
	public:
		ILayer* layer;

		DrawEvent(Camera* engine , ILayer* layer);

	public:
		SpriteEngine* sprite_engine();

		void mask_draw_begin() const;
		void mask_discard_begin(bool increase_layer = true);
		void mask_discard_end(bool decrease_layer = true);
		void mask_set_stencil(BYTE new_index);
		BYTE mask_get_stencil_layer();
		void mask_clear();

		void set_alpha(float alpha);
		
		void draw_vertex(UINT count, UINT start = 0) const;
		void draw_object(Canvas::I2DCanvasObject*object);
	};
}
