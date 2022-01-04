#pragma once
#include "../d3d/Buffer/ConstantBuffer.h"
#include "../Engine/PrimitiveTopology.h"
#include <DirectXMath.h>

#include "GraphicsCommon.h"
#include "MaskEngine.h"

namespace Render
{
	class PixelShader;
	class VertexShader;
	class SamplerState;
	
	class IGContext
	{
	protected:
		IGContext(Core::GraphicsContext* context)
			: matrix_buffer(context),
			control_buffer(context,1,CBBindFlag_vs | CBBindFlag_ps)
		{}
	public:
		virtual ~IGContext() = default;

		__declspec(align(16))
			struct MatrixBufferStruct
		{
			DirectX::XMMATRIX MVPMatrix;
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

		virtual void debug_message(const char* message) =0;

		virtual void set_topology(PrimitiveTopology topology) =0;
		virtual void set_pixel_shader(PixelShader* ps) =0;
		virtual void set_vertex_shader(VertexShader* vs) = 0;
		virtual void set_mask_engine(GEMaskEngine* mask) =0;
		virtual void set_sampler_state(SamplerState* sampler) =0;
		virtual void draw_indexed(UINT count, UINT start_location=0,UINT base_vertex_location=0) = 0;
		virtual void draw(UINT count, UINT start_location) = 0;

		virtual void set_render_target(RenderTarget* target) = 0;
		virtual void set_render_target(RenderTarget* target, GEMaskEngine* mask) =0;
		virtual void set_shader_resource(GETexture* texture,UINT slot=0) =0;
		void set_shader_resource(GEMaskEngine*mask,UINT slot=0);
		void set_shader_resource(RenderTarget* rt, UINT slot = 0);
		virtual void set_rasterizer(GERasterizer& rs) =0;

		virtual GERasterizer get_rasterizer()=0;

		virtual PixelShader* get_pixel_shader() =0;
		virtual VertexShader* get_vertex_shader() =0;
	};

	inline void IGContext::set_shader_resource(GEMaskEngine* mask, UINT slot)
	{
		set_shader_resource(mask->get_texture(), slot);
	}

	inline void IGContext::set_shader_resource(RenderTarget* rt,UINT slot)
	{
		set_shader_resource(rt->get_texture(),slot);
	}
}
