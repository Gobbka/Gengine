#include "MaskEngine.h"
#include "Camera.h"
#include "Types/Types.h"

Render::MaskEngine::MaskEngine(Core::GraphicsContext* engine)
	: Bindable(engine)
{
	auto screen_resolution = engine->get_screen_resolution();
	auto* device = _engine->device;
	
	D3D11_TEXTURE2D_DESC texture_2d_desc{};
	
	texture_2d_desc.Width = (UINT)screen_resolution.width;
	texture_2d_desc.Height = (UINT)screen_resolution.height;
	texture_2d_desc.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	texture_2d_desc.ArraySize = 1;
	texture_2d_desc.MipLevels = 1;
	texture_2d_desc.SampleDesc = { 1,0 };
	texture_2d_desc.Usage = D3D11_USAGE_DEFAULT;
	texture_2d_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texture_2d_desc.MiscFlags = 0;
	texture_2d_desc.CPUAccessFlags = 0;

	assert(SUCCEEDED(device->CreateTexture2D(&texture_2d_desc,nullptr,&_buffer)));

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	descDSV.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	assert(SUCCEEDED(device->CreateDepthStencilView(_buffer, &descDSV, &_view)));

	D3D11_DEPTH_STENCIL_DESC depthstencildesc{};

	depthstencildesc.DepthEnable = false;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;

	depthstencildesc.StencilEnable = 1;
	depthstencildesc.StencilReadMask = 0XFF;
	depthstencildesc.StencilWriteMask = 0XFF;
	// COMPARISON_ALWAYS
	depthstencildesc.FrontFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_EQUAL; //In the default stencil state, always pass, don't even do a comparison function
	depthstencildesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP; //KEEP STENCIL BUFFER VALUE (WILL NEVER FAIL SO TECHNICALLY IRRELEVANT)

	depthstencildesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	depthstencildesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP; //KEEP STENCIL BUFFER VALUE (DEPTH IS DISABLED SO SHOULD NEVER FAIL? TECHNICALLY IRRELEVANT)

	// We are not rendering backfaces, so never run any comparison function on backface (D3D11_COMPARISON_NEVER)
	depthstencildesc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
	depthstencildesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP; //NOT RELEVANT, TEST NEVER OCCURS
	depthstencildesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP; //NOT RELEVANT, TEST NEVER OCCURS
	depthstencildesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP; //NOT RELEVANT, TEST NEVER OCCURS

	assert(SUCCEEDED(device->CreateDepthStencilState(&depthstencildesc, &_drawState)));

	//Discard blend state (Just need to change a few things from default depth stencil)
	depthstencildesc.FrontFace.StencilFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_EQUAL;
	depthstencildesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP; //KEEP STENCIL BUFFER VALUE (same as default)
	depthstencildesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP; //KEEP STENCIL BUFFER VALUE (Notice in default we incremented, but in this we don't! We only want to compare to the stencil value written by the previous stencil state)
	depthstencildesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP; //KEEP STENCIL BUFFER VALUE (same as default)

	assert(SUCCEEDED(device->CreateDepthStencilState(&depthstencildesc, &_discardState)));

	CD3D11_DEPTH_STENCIL_DESC defstate(D3D11_DEFAULT);
	defstate.DepthEnable = true;
	defstate.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	defstate.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;

	assert(SUCCEEDED(device->CreateDepthStencilState(&depthstencildesc, &_disabledState)));

	set_state(_disabledState);
}

void Render::MaskEngine::set_state(ID3D11DepthStencilState* state, UINT reference)
{
	_currentState = state;
	_engine->context->OMSetDepthStencilState(state, reference);
}

void Render::MaskEngine::clear_buffer()
{
	_engine->context->ClearDepthStencilView(_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 0, 0);
}

void Render::MaskEngine::bind()
{
	
	auto* nigger = _engine->get_render_target_view();
	_engine->context->OMSetRenderTargets(1, &nigger, _view);
}
