#pragma once
#include "Render/d3d/Buffer/ConstantBuffer.h"
#include "Graphics/PrimitiveTopology.h"

namespace Render
{
	class MaskEngine;
	
	class IGContext
	{
	protected:
		IGContext(Core::GraphicsContext* context)
			: matrix_buffer(context),
			control_buffer(context,1,CBBindFlag_vs | CBBindFlag_ps)
		{}
	public:
		__declspec(align(16))
			struct MatrixBufferStruct
		{
			DirectX::XMMATRIX VPMatrix;
			DirectX::XMMATRIX ModelMatrix;
		};

		__declspec(align(16))
			struct ControlBufferStruct
		{
			float opacity = 1.f;
		};
		
	public:
		ConstantBuffer<MatrixBufferStruct> matrix_buffer;
		ConstantBuffer<ControlBufferStruct> control_buffer;

		virtual void set_topology(PrimitiveTopology topology) =0;
		virtual void set_pixel_shader(PixelShader* ps) =0;
		virtual void set_vertex_shader(VertexShader* vs) = 0;
		virtual void set_mask_engine(MaskEngine* mask) =0;
		virtual void draw_indexed(UINT count, UINT start_location=0) = 0;

		virtual PixelShader* get_pixel_shader() =0;
	};
}
