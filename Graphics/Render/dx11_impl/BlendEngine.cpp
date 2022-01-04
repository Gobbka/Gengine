#include "BlendEngine.h"

#include "../../Graphics.h"
#include "Logger/Logger.h"

Render::DX11BlendEngine::DX11BlendEngine(GEGraphics* engine)
	: Bindable(engine)
	, _blend(nullptr)
{
	D3D11_RENDER_TARGET_BLEND_DESC rtbd{};

	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	rtbd.DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

	D3D11_BLEND_DESC blendDesc{};
	blendDesc.RenderTarget[0] = rtbd;

	GEAssert(_engine->device->CreateBlendState(&blendDesc, &_blend))
		.abort(TEXT("BlendEngine.cpp: cannot create blend state"));
}

void Render::DX11BlendEngine::bind()
{
	_engine->context->OMSetBlendState(_blend, 0, 0xFFFFFFFF);
}
