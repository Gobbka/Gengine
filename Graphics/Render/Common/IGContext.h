#pragma once
#include "../d3d/Buffer/ConstantBuffer.h"
#include "../../Graphics/PrimitiveTopology.h"
#include <DirectXMath.h>

#include "GraphicsCommon.h"
#include "MaskEngine.h"

namespace Render
{
	class PixelShader;
	class VertexShader;
	
	class IGContext
	{
	protected:
		IGContext(GEGraphics* context)
		{}
	public:
		virtual ~IGContext() = default;
		
	public:

		virtual void debug_message(const char* message) =0;

		virtual void set_topology(PrimitiveTopology topology) =0;
		virtual void set_pixel_shader(PixelShader* ps) =0;
		virtual void set_vertex_shader(VertexShader* vs) = 0;
		virtual void set_mask_engine(GEMaskEngine* mask) =0;
		virtual void set_sampler_state(GESamplerState* sampler) =0;
		virtual void draw_indexed(UINT count, UINT start_location=0,UINT base_vertex_location=0) = 0;
		virtual void draw(UINT count, UINT start_location) = 0;

		virtual void set_render_target(GERenderTarget* target) = 0;
		virtual void set_render_target(GERenderTarget* target, GEMaskEngine* mask) =0;
		virtual void set_shader_resource(GETexture* texture,UINT slot=0) =0;
		void set_shader_resource(GEMaskEngine*mask,UINT slot=0);
		void set_shader_resource(GERenderTarget* rt, UINT slot = 0);
		virtual void set_rasterizer(GERasterizer& rs) =0;

		virtual GERasterizer get_rasterizer()=0;

		virtual PixelShader* get_pixel_shader() =0;
		virtual VertexShader* get_vertex_shader() =0;
	};

	inline void IGContext::set_shader_resource(GEMaskEngine* mask, UINT slot)
	{
		set_shader_resource(mask->get_texture(), slot);
	}

	inline void IGContext::set_shader_resource(GERenderTarget* rt,UINT slot)
	{
		set_shader_resource(rt->get_texture(),slot);
	}
}
