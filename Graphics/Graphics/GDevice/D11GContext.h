#pragma once
#include "../../IGContext.h"

namespace Render {
	class D11GContext final : public IGContext
	{
		PrimitiveTopology _current_topology = PrimitiveTopology::NONE;
		ID3D11DeviceContext* _d11context;
		PixelShader* _current_ps;
		VertexShader* _currect_vs;
	public:
		D11GContext(Core::GraphicsContext* context,ID3D11DeviceContext*d11context);

		void set_topology(PrimitiveTopology topology) override;
		void set_pixel_shader(PixelShader* ps) override;
		void set_vertex_shader(VertexShader* vs) override;
		void set_mask_engine(MaskEngine* mask) override;

		void draw_indexed(UINT count, UINT start_location=0) override;

		PixelShader* get_pixel_shader() override;
	};
}