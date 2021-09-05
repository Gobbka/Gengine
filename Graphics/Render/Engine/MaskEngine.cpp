#include "MaskEngine.h"
#include "Camera.h"
#include "Types/Types.h"

D3D11_DEPTH_STENCILOP_DESC create_depth_stencilop_desc(D3D11_COMPARISON_FUNC stencil_func,D3D11_STENCIL_OP success_func)
{
	return D3D11_DEPTH_STENCILOP_DESC{ D3D11_STENCIL_OP_KEEP,D3D11_STENCIL_OP_KEEP,success_func,stencil_func };
}

Render::Stencil::Stencil(Core::GraphicsContext* context, StencilUsage usage)
{
	_context = context->context;
	_state = nullptr;

	D3D11_DEPTH_STENCIL_DESC depthstencildesc = {};

	// i dont know why, but ui wont work when DepthEnable equals true
	depthstencildesc.DepthEnable = false;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthstencildesc.StencilEnable = 1;
	depthstencildesc.StencilReadMask = 0XFF;
	depthstencildesc.StencilWriteMask = 0XFF;

	switch(usage)
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
		depthstencildesc.StencilEnable = false;
		depthstencildesc.DepthEnable = true;
	break;
	}

	assert(SUCCEEDED(context->device->CreateDepthStencilState(&depthstencildesc, &_state)));
}

void Render::Stencil::bind(UINT reference) const
{
	_context->OMSetDepthStencilState(_state, reference);
}

Render::Stencil::~Stencil()
{
	if (_state)
		_state->Release();
}

Render::MaskEngine::MaskEngine(WorldViewer* target, MaskEngineUsage usage,Surface*resolution)
	: Bindable(target->graphics_context()),
	_disabledState(target->graphics_context(), StencilUsage::normal),
	_drawState(target->graphics_context(), usage == MaskEngineUsage::DepthStencil ? StencilUsage::write : StencilUsage::normal),
	_discardState(target->graphics_context(), usage == MaskEngineUsage::DepthStencil ? StencilUsage::mask : StencilUsage::normal),
	_currentState(nullptr),
	_view(nullptr)
{
	_target = target->get_render_target();
	
	auto screen_resolution = resolution == nullptr ? target->get_view_resolution() : *resolution;
	auto* device = _engine->device;
	
	D3D11_TEXTURE2D_DESC texture_2d_desc{};
	
	texture_2d_desc.Width = (UINT)screen_resolution.width;
	texture_2d_desc.Height = (UINT)screen_resolution.height;
	texture_2d_desc.Format = usage == MaskEngineUsage::DepthStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
	texture_2d_desc.ArraySize = 1;
	texture_2d_desc.MipLevels = 1;
	texture_2d_desc.SampleDesc = { 1,0 };
	texture_2d_desc.Usage = D3D11_USAGE_DEFAULT;
	texture_2d_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texture_2d_desc.MiscFlags = 0;
	texture_2d_desc.CPUAccessFlags = 0;

	assert(SUCCEEDED(device->CreateTexture2D(&texture_2d_desc,nullptr,&_buffer)));

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_UNKNOWN;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	assert(SUCCEEDED(device->CreateDepthStencilView(_buffer, &descDSV, &_view)));
}

void Render::MaskEngine::set_state(Stencil* state, UINT reference,bool force)
{
	if (_currentState == state && !force)
		return;

	_currentState = state;
	_currentState->bind(reference);
}

void Render::MaskEngine::clear_buffer() const
{
	_engine->context->ClearDepthStencilView(_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void Render::MaskEngine::bind()
{
	_target->bind(_view);
}
