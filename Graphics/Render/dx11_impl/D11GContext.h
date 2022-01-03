#pragma once
#include <d3d11.h>
#include "../Common/IGContext.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render {
	class SamplerState;
	class VertexShader;
	class PixelShader;

	class D11GContext final : public IGContext
	{
		ID3D11InfoQueue* _info_queue;
		ID3D11DeviceContext* _d11context;
		PrimitiveTopology _current_topology;
		PixelShader* _current_ps;
		VertexShader* _currect_vs;
		SamplerState* _current_sampler;
	public:
		D11GContext(ID3D11DeviceContext*d11context, Core::GraphicsContext* context);

		void set_topology(PrimitiveTopology topology) override;
		void set_pixel_shader(PixelShader* ps) override;
		void set_vertex_shader(VertexShader* vs) override;
		void set_mask_engine(MaskEngine* mask) override;
		void set_sampler_state(SamplerState* sampler) override;
		void set_render_target(RenderTarget* target, MaskEngine* mask) override;
		void set_render_target(RenderTarget* target) override;
		void set_shader_resource(Texture* texture,UINT slot) override;
		void set_rasterizer(Rasterizer& rs) override;
		void draw_indexed(UINT count, UINT start_location=0,UINT base_vertex_location=0) override;
		void draw(UINT count, UINT start_location) override;
		void debug_message(const char* message) override;

		Rasterizer get_rasterizer() override;
		PixelShader* get_pixel_shader() override;
		VertexShader* get_vertex_shader() override;
	};
}
