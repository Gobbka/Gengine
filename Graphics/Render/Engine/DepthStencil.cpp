#include "DepthStencil.h"
#include "../../Graphics.h"

D3D11_DEPTH_STENCILOP_DESC create_depth_stencilop_desc(D3D11_COMPARISON_FUNC stencil_func, D3D11_STENCIL_OP success_func)
{
	return D3D11_DEPTH_STENCILOP_DESC{ D3D11_STENCIL_OP_KEEP,D3D11_STENCIL_OP_KEEP,success_func,stencil_func };
}

Render::DepthStencil::DepthStencil(Core::GraphicsContext* context, DepthStencilDesc desc)
	:
	_context(context->context),
	_state(nullptr)
{
	D3D11_DEPTH_STENCIL_DESC depthstencildesc = {};

	depthstencildesc.DepthEnable = desc.depth;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthstencildesc.StencilEnable = 1;
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
		break;
	}

	context->device->CreateDepthStencilState(&depthstencildesc, &_state);
}

Render::DepthStencil::DepthStencil(DepthStencil& other)
	:
	_context(other._context),
	_state(nullptr)
{
	D3D11_DEPTH_STENCIL_DESC desc;
	ID3D11Device* device;

	other._state->GetDesc(&desc);
	_context->GetDevice(&device);

	device->CreateDepthStencilState(&desc, &_state);
}

Render::DepthStencil::DepthStencil(DepthStencil&& other) noexcept
	:
	_context(other._context),
	_state(other._state)
{
	other._state = nullptr;
}

Render::DepthStencil::~DepthStencil()
{
	if (_state)
		_state->Release();
}

Render::DepthStencil& Render::DepthStencil::operator=(DepthStencil&& other) noexcept
{
	if (_state && _state != other._state)
		_state->Release();

	_state = other._state;
	other._state = nullptr;

	return*this;
}

void Render::DepthStencil::bind(unsigned reference) const
{
	_context->OMSetDepthStencilState(_state, reference);
}
