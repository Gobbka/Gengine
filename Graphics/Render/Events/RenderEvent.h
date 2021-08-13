#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

namespace Core {
	class GraphicsContext;
}

namespace Canvas
{
	class Canvas2DLayer;
	class I2DCanvasObject;
}

namespace Render {
	class Model;
	class SpriteEngine;
	class Camera;

	struct __declspec(dllexport) DrawEvent {
	protected:
		Camera* _camera;
	private:
		UINT _stencil_layer = 0u;
		
	public:
		DrawEvent(Camera* engine);

	public:
		SpriteEngine* sprite_engine();

		void mask_draw_begin() const;
		void mask_discard_begin(bool increase_layer = true);
		void mask_discard_end(bool decrease_layer = true);
		void mask_set_stencil(BYTE new_index);
		BYTE mask_get_stencil_layer();
		void mask_clear();

		void set_alpha(float alpha);
		
	};

	struct __declspec(dllexport) DrawEvent2D : public DrawEvent{
	private:
		UINT _draw_index = 0u;
	public:
		Canvas::Canvas2DLayer* layer;
		DrawEvent2D(Camera* camera, Canvas::Canvas2DLayer*layer);
		
		void draw_vertex(UINT count, UINT start = 0) const;
		void draw_object(Canvas::I2DCanvasObject* object);
	};

	struct DrawEvent3D
	{
		Core::GraphicsContext* _context;
	public:
		
		DrawEvent3D(Core::GraphicsContext* context);

		void draw(UINT count,UINT start_location = 0);
		void draw_indexed(UINT count,UINT start_location = 0);
		
		void draw_object(Model* object);
	};
}
