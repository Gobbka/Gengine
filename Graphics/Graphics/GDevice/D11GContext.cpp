#include "D11GContext.h"

#include "../../Render/d3d/Shader/PixelShader.h"
#include "../../Render/d3d/Shader/SamplerState.h"
#include "../../Render/d3d/Shader/VertexShader.h"
#include "../../Render/Engine/MaskEngine.h"

Render::D11GContext::D11GContext(Core::GraphicsContext* context, ID3D11DeviceContext* d11context)
	: IGContext(context),
	_current_topology(PrimitiveTopology::NONE),
	_d11context(d11context),
	_current_ps(nullptr),
	_currect_vs(nullptr),
	_current_sampler(nullptr)
{}

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
	default:
		_d11context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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

	const auto num_view = target_view == nullptr ? 0 : 1;
	const auto* pp_target = target_view == nullptr ? nullptr : &target_view;
	
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

void Render::D11GContext::set_render_target(RenderTarget* target, MaskEngine* mask)
{
	auto* mask_view = mask == nullptr ? nullptr : mask->get_view();
	if(target == nullptr)
	{
		_d11context->OMSetRenderTargets(0, nullptr, mask_view);
	}else
	{
		auto* view = target->get_view();
		_d11context->OMSetRenderTargets(1, &view, mask_view);
	}
}

void Render::D11GContext::set_render_target(RenderTarget* target)
{
	ID3D11DepthStencilView* old_view;
	_d11context->OMGetRenderTargets(0, nullptr, &old_view);

	if(target == nullptr)
	{
		_d11context->OMSetRenderTargets(0, nullptr, old_view);
	}else
	{
		auto* r_view = target->get_view();
		_d11context->OMSetRenderTargets(1, &r_view, old_view);
	}
}

void Render::D11GContext::set_shader_resource(Texture* texture,UINT slot)
{
	if(texture != nullptr)
	{
		texture->bind(slot);
	}else
	{
		ID3D11ShaderResourceView* resource = nullptr;
		_d11context->PSSetShaderResources(slot, 1, &resource);
	}
}

void Render::D11GContext::set_rasterizer(Rasterizer& rs)
{
	_d11context->RSSetState(rs._rs);
}

void Render::D11GContext::draw_indexed(UINT count, UINT start_location)
{
	_d11context->DrawIndexed(count, start_location, 0);
}

Render::Rasterizer Render::D11GContext::get_rasterizer()
{
	ID3D11RasterizerState* rs=nullptr;
	_d11context->RSGetState(&rs);
	return {rs};
}

Render::PixelShader* Render::D11GContext::get_pixel_shader()
{
	return _current_ps;
}
