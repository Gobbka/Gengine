#pragma once
#include <vector>

#include "../../Graphics.h"
#include "../d3d/Buffer/ConstantBuffer.h"
#include "../Layer/ILayer.h"

namespace Render
{
	class MaskEngine;
	class BlendEngine;

	class D3DEngine
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
	public:
		bool create_buffer(D3D11_BUFFER_DESC* desc,D3D11_SUBRESOURCE_DATA*data,ID3D11Buffer**buffer) const;
		void set_resolution(Surface new_resolution);
		void set_alpha(float alpha);
	public:
		ID3D11DeviceContext* context() const;
		ID3D11Device* device() const;
		ID3D11RenderTargetView* get_target_view() const;
		MaskEngine* mask_engine() const;
		BlendEngine* blend_engine() const;

		Surface get_screen_resolution() const;
	public:
		
		D3DEngine(Core::GraphicsContext* context);

		void present(DrawEvent* event);
	};
}
