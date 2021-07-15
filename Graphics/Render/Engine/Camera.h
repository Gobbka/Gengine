#pragma once
#include <vector>

#include "../../Graphics.h"
#include "../d3d/Buffer/ConstantBuffer.h"
#include "../Layer/ILayer.h"

namespace Render
{
	class MaskEngine;
	class BlendEngine;

	class __declspec(dllexport) Camera
	{
	private:
		Core::GraphicsContext* _context;

		__declspec(align(16))
		struct
		{
			float width;
			float height;
			float alpha;
		} _b0_constant_buffer_struct;

		ConstantBuffer* b0_buffer;

		BlendEngine* _blendEngine;
		MaskEngine*  _maskEngine;

		std::vector<Canvas::Canvas2DLayer*> _canvas2DLayers;
	public:
		void set_resolution(Surface new_resolution);
		void set_alpha(float alpha);

		Canvas::Canvas2DLayer* create_canvas_2d();
		void register_canvas_2d(Canvas::Canvas2DLayer* layer);
	public:
		Core::GraphicsContext* graphics_context();
		ID3D11DeviceContext* context() const;
		ID3D11Device* device() const;
		ID3D11RenderTargetView* get_target_view() const;
		MaskEngine* mask_engine() const;
		BlendEngine* blend_engine() const;

		Surface get_screen_resolution() const;
	public:
		
		Camera(Core::GraphicsContext* context);

		void present(DrawEvent* event);
	};
}
