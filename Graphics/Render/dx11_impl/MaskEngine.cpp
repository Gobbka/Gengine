#include "MaskEngine.h"

#include "../../Graphics.h"
#include "../../Graphics/Camera.h"
#include "Types/Types.h"
#include "../Common/RenderTarget.h"
#include "Logger/Logger.h"

#define MAP_USAGE_TYPELESS(usage) usage == MaskEngineUsage::DepthStencil ? DXGI_FORMAT_R24G8_TYPELESS : DXGI_FORMAT_R32_TYPELESS
#define MAP_USAGE_TYPED(usage) usage == MaskEngineUsage::DepthStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT

Render::DX11MaskEngine::DX11MaskEngine(DX11RenderTarget* target, MaskEngineUsage usage)
	: _context(target->get_context())
	, _buffer(nullptr)
	, _view(nullptr)
	, _target(target)
{
	const auto screen_resolution = _target->get_texture()->resolution();
	auto* device = _context->device;
	
	D3D11_TEXTURE2D_DESC texture_2d_desc{};
	
	texture_2d_desc.Width = (UINT)screen_resolution.width;
	texture_2d_desc.Height = (UINT)screen_resolution.height;
	texture_2d_desc.Format = MAP_USAGE_TYPELESS(usage);
	texture_2d_desc.ArraySize = 1;
	texture_2d_desc.MipLevels = 1;
	texture_2d_desc.SampleDesc = { 1,0 };
	texture_2d_desc.Usage = D3D11_USAGE_DEFAULT;
	texture_2d_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	texture_2d_desc.MiscFlags = 0;
	texture_2d_desc.CPUAccessFlags = 0;

	ID3D11Texture2D* texture_2d;

	GEAssert(device->CreateTexture2D(&texture_2d_desc, nullptr, &texture_2d))
		.abort(TEXT("MaskEngine.cpp: cannot create mask engine from RenderTarget"));

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = MAP_USAGE_TYPED(usage);
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	GEAssert(device->CreateDepthStencilView(texture_2d, &descDSV, &_view))
		.abort(TEXT("MaskEngine.cpp: cannot create depth stencil view"));

	_buffer = GETexture(_context, texture_2d);
}

Render::DX11MaskEngine::DX11MaskEngine(GEGraphics* context, Surface resolution, MaskEngineUsage usage)
	: _context(context)
	, _buffer(nullptr)
	, _view(nullptr)
	, _target(nullptr)
{
	auto* device = context->device;

	D3D11_TEXTURE2D_DESC texture_2d_desc{};

	texture_2d_desc.Width = (UINT)resolution.width;
	texture_2d_desc.Height = (UINT)resolution.height;
	texture_2d_desc.Format = usage == MaskEngineUsage::DepthStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
	texture_2d_desc.ArraySize = 1;
	texture_2d_desc.MipLevels = 1;
	texture_2d_desc.SampleDesc = { 1,0 };
	texture_2d_desc.Usage = D3D11_USAGE_DEFAULT;
	texture_2d_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texture_2d_desc.MiscFlags = 0;
	texture_2d_desc.CPUAccessFlags = 0;

	ID3D11Texture2D* texture_2d;

	GEAssert(device->CreateTexture2D(&texture_2d_desc, nullptr, &texture_2d))
		.abort(TEXT("MaskEngine.cpp: cannot create MaskEngine from MaskEngineUsage"));

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_UNKNOWN;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	GEAssert(device->CreateDepthStencilView(texture_2d, &descDSV, &_view))
		.abort(TEXT("MaskEngine.cpp: cannot create depth stencil view"));

	_buffer = GETexture(_context, texture_2d);
}

void Render::DX11MaskEngine::clear_buffer() const
{
	_context->context->ClearDepthStencilView(_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

Render::GETexture* Render::DX11MaskEngine::get_texture()
{
	return &_buffer;
}
