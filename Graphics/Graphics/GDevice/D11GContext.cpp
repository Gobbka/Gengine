#include "D11GContext.h"

#include "../../Render/d3d/Shader/PixelShader.h"
#include "../../Render/d3d/Shader/SamplerState.h"
#include "../../Render/d3d/Shader/VertexShader.h"
#include "../../Render/Engine/MaskEngine.h"

Render::D11GContext::D11GContext(Core::GraphicsContext* context, ID3D11DeviceContext* d11context)
	: IGContext(context)
{
	_d11context = d11context;
}

void Render::D11GContext::set_topology(PrimitiveTopology topology)
{
	if (topology == _current_topology)
		return;
	
	switch (topology)
	{
	case PrimitiveTopology::TRIANGLELIST:
		_d11context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case PrimitiveTopology::TRIANGLESTRIP:
		_d11context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		break;
	}
	_current_topology = topology;
}

void Render::D11GContext::set_pixel_shader(PixelShader* ps)
{
	if (ps == _current_ps)
		return;
	auto* shader = ps == nullptr ? nullptr : ps->get_d3d11_ps();
	_d11context->PSSetShader(shader, nullptr, 0);
	_current_ps = ps;
}

void Render::D11GContext::set_vertex_shader(VertexShader* vs)
{
	if (vs == _currect_vs)
		return;
	_d11context->VSSetShader(vs->get_d11_vs(), nullptr, 0);
	_currect_vs = vs;
}

void Render::D11GContext::set_mask_engine(MaskEngine* mask)
{
	ID3D11RenderTargetView* target_view;
	_d11context->OMGetRenderTargets(1, &target_view, nullptr);

	auto num_view = target_view == nullptr ? 0 : 1;
	auto* pp_target = target_view == nullptr ? nullptr : &target_view;
	
	_d11context->OMSetRenderTargets(num_view,pp_target, mask->get_view());
}

void Render::D11GContext::set_sampler_state(SamplerState* sampler)
{
	if(sampler != _current_sampler)
	{
		sampler->bind();
	}

	_current_sampler = sampler;
}

void Render::D11GContext::draw_indexed(UINT count, UINT start_location)
{
	_d11context->DrawIndexed(count, start_location, 0);
}

Render::PixelShader* Render::D11GContext::get_pixel_shader()
{
	return _current_ps;
}
