#include "D11GContext.h"

#include "../../Render/d3d/Shader/PixelShader.h"
#include "../../Render/Engine/MaskEngine.h"

Render::D11GContext::D11GContext(Core::GraphicsContext* context, ID3D11DeviceContext* d11context)
	: IGContext(context)
{
	_d11context = d11context;
}

void Render::D11GContext::set_topology(PrimitiveTopology topology)
{
	switch (topology)
	{
	case PrimitiveTopology::TRIANGLELIST:
		_d11context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case PrimitiveTopology::TRIANGLESTRIP:
		_d11context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		break;
	}
}

void Render::D11GContext::set_pixel_shader(PixelShader* ps)
{
	if (ps == _current_ps)
		return;
	auto* shader = ps->get_d3d11_ps();
	_d11context->PSSetShader(shader, nullptr, 0);
	_current_ps = ps;
}

void Render::D11GContext::set_mask_engine(MaskEngine* mask)
{
	ID3D11RenderTargetView* target_view;
	_d11context->OMGetRenderTargets(1, &target_view, nullptr);

	auto num_view = target_view == nullptr ? 0 : 1;
	auto* pp_target = target_view == nullptr ? nullptr : &target_view;
	
	_d11context->OMSetRenderTargets(num_view,pp_target, mask->get_view());
}

Render::PixelShader* Render::D11GContext::get_pixel_shader()
{
	return _current_ps;
}
