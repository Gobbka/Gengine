#include "DepthStencil.h"
#include "../../Graphics.h"

D3D11_COMPARISON_FUNC get_d3d11_comparison_func(Render::DepthFunc func)
{
	switch (func)
	{
	case Render::DepthFunc::none:
		return D3D11_COMPARISON_NEVER;
	case Render::DepthFunc::depth_less:
		return D3D11_COMPARISON_LESS;
	case Render::DepthFunc::depth_equal:
		return D3D11_COMPARISON_EQUAL;
	}
}

D3D11_DEPTH_STENCILOP_DESC create_depth_stencilop_desc(D3D11_COMPARISON_FUNC stencil_func, D3D11_STENCIL_OP success_func)
{
	return D3D11_DEPTH_STENCILOP_DESC{ D3D11_STENCIL_OP_KEEP,D3D11_STENCIL_OP_KEEP,success_func,stencil_func };
}

Render::DepthStencil::DepthStencil()
{
	_context = nullptr;
	_state = nullptr;
}

Render::DepthStencil::DepthStencil(Core::GraphicsContext* context, DepthStencilDesc desc)
	:
	_context(context->context),
	_state(nullptr)
{
	D3D11_DEPTH_STENCIL_DESC depthstencildesc = {};

	depthstencildesc.DepthEnable = desc.depth != DepthFunc::none;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = get_d3d11_comparison_func(desc.depth);

	depthstencildesc.StencilEnable = desc.stencil_usage != StencilUsage::none;
	depthstencildesc.StencilReadMask = 0XFF;
	depthstencildesc.StencilWriteMask = 0XFF;

	switch (desc.stencil_usage)
	{
	case StencilUsage::write:
		depthstencildesc.FrontFace = create_depth_stencilop_desc(D3D11_COMPARISON_EQUAL, D3D11_STENCIL_OP_INCR);
		depthstencildesc.BackFace = create_depth_stencilop_desc(D3D11_COMPARISON_NEVER, D3D11_STENCIL_OP_KEEP);
		break;
	case StencilUsage::mask:
		depthstencildesc.BackFace = create_depth_stencilop_desc(D3D11_COMPARISON_NEVER, D3D11_STENCIL_OP_KEEP);
		depthstencildesc.FrontFace = create_depth_stencilop_desc(D3D11_COMPARISON_EQUAL, D3D11_STENCIL_OP_KEEP);
		break;
	case StencilUsage::normal:
		depthstencildesc.BackFace = create_depth_stencilop_desc(D3D11_COMPARISON_NEVER, D3D11_STENCIL_OP_KEEP);
		depthstencildesc.FrontFace = create_depth_stencilop_desc(D3D11_COMPARISON_NEVER, D3D11_STENCIL_OP_KEEP);
		break;
	case StencilUsage::none: break;
	default: ;
	}

	context->device->CreateDepthStencilState(&depthstencildesc, &_state);
}

void Render::DepthStencil::bind(unsigned reference) const
{
	_context->OMSetDepthStencilState(_state, reference);
}

bool Render::DepthStencil::valid() const
{
	return !!_state;
}
