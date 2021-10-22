#include "MaskEngine.h"

#include "../../Graphics.h"
#include "Camera.h"
#include "Types/Types.h"
#include "RenderTarget.h"

#define MAP_USAGE_TYPELESS(usage) usage == MaskEngineUsage::DepthStencil ? DXGI_FORMAT_R24G8_TYPELESS : DXGI_FORMAT_R32_TYPELESS
#define MAP_USAGE_TYPED(usage) usage == MaskEngineUsage::DepthStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT

Render::MaskEngine::MaskEngine(RenderTarget* target, MaskEngineUsage usage)
	:
	_context(target->get_context()),
	_buffer(nullptr),
	_view(nullptr),
	_target(target)
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

	assert(SUCCEEDED(device->CreateTexture2D(&texture_2d_desc,nullptr,&_buffer)));

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = MAP_USAGE_TYPED(usage);
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	assert(SUCCEEDED(device->CreateDepthStencilView(_buffer, &descDSV, &_view)));
}

Render::MaskEngine::MaskEngine(Core::GraphicsContext* context, Surface resolution, MaskEngineUsage usage)
	: _context(context),
	_buffer(nullptr),
	_view(nullptr),
	_target(nullptr)
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

	assert(SUCCEEDED(device->CreateTexture2D(&texture_2d_desc, nullptr, &_buffer)));

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_UNKNOWN;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	assert(SUCCEEDED(device->CreateDepthStencilView(_buffer, &descDSV, &_view)));
}

void Render::MaskEngine::clear_buffer() const
{
	_context->context->ClearDepthStencilView(_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}
