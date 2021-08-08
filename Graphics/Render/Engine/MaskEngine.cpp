#include "MaskEngine.h"
#include "Camera.h"
#include "Types/Types.h"

D3D11_DEPTH_STENCILOP_DESC create_depth_stencilop_desc(D3D11_COMPARISON_FUNC stencil_func,D3D11_STENCIL_OP success_func)
{
	return D3D11_DEPTH_STENCILOP_DESC{ D3D11_STENCIL_OP_KEEP,D3D11_STENCIL_OP_KEEP,success_func,stencil_func };
}

Render::MaskEngine::MaskEngine(Core::GraphicsContext* engine)
	: Bindable(engine)
{
	auto screen_resolution = engine->get_screen_resolution();
	auto* device = _engine->device;
	
	D3D11_TEXTURE2D_DESC texture_2d_desc{};
	
	texture_2d_desc.Width = (UINT)screen_resolution.width;
	texture_2d_desc.Height = (UINT)screen_resolution.height;
	texture_2d_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
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

	D3D11_DEPTH_STENCIL_DESC depthstencildesc = {};
	// i dont know why, but ui wont work when DepthEnable equals true
	depthstencildesc.DepthEnable = false;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthstencildesc.StencilEnable = 1;
	depthstencildesc.StencilReadMask = 0XFF;
	depthstencildesc.StencilWriteMask = 0XFF;
	// COMPARISON_ALWAYS
	depthstencildesc.FrontFace = create_depth_stencilop_desc(D3D11_COMPARISON_EQUAL, D3D11_STENCIL_OP_INCR);
	depthstencildesc.BackFace = create_depth_stencilop_desc(D3D11_COMPARISON_NEVER, D3D11_STENCIL_OP_KEEP);
	
	assert(SUCCEEDED(device->CreateDepthStencilState(&depthstencildesc, &_drawState)));
	
	depthstencildesc.FrontFace = create_depth_stencilop_desc(D3D11_COMPARISON_EQUAL, D3D11_STENCIL_OP_KEEP);
	
	assert(SUCCEEDED(device->CreateDepthStencilState(&depthstencildesc, &_discardState)));
	
	CD3D11_DEPTH_STENCIL_DESC defstate(D3D11_DEFAULT);
	defstate.DepthEnable = true;
	defstate.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	defstate.DepthFunc = D3D11_COMPARISON_LESS;
	
	assert(SUCCEEDED(device->CreateDepthStencilState(&defstate, &_disabledState)));
	
	set_state(_disabledState);
}

void Render::MaskEngine::set_state(ID3D11DepthStencilState* state, UINT reference)
{
	if (_currentState == state)
		return;
	set_state_force(state, reference);
}

void Render::MaskEngine::set_state_force(ID3D11DepthStencilState* state, UINT reference)
{
	_currentState = state;
	_engine->context->OMSetDepthStencilState(state, reference);
}

void Render::MaskEngine::clear_buffer()
{
	_engine->context->ClearDepthStencilView(_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void Render::MaskEngine::bind()
{
	_engine->get_render_target_view()->bind(_view);
}
