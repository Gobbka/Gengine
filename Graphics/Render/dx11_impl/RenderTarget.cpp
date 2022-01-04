#include "RenderTarget.h"

#include "../../Graphics.h"
#include "Logger/Logger.h"

Render::DX11RenderTarget::DX11RenderTarget(Core::GraphicsContext* context, IDXGISwapChain* swap)
	:  _targetView(nullptr)
	, _context(context)
	, _texture(context)
{
	ID3D11Resource* back_buffer = nullptr;
	swap->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&back_buffer);

	D3D11_TEXTURE2D_DESC desc;
	((ID3D11Texture2D*)back_buffer)->GetDesc(&desc);

	GEAssert(back_buffer != nullptr)
		.abort(TEXT("RenderTarget.cpp: cannot get back buffer from IDXGISwapChain"));

	GEAssert(context->device->CreateRenderTargetView(back_buffer, nullptr, &_targetView))
		.abort(TEXT("RenderTarget.cpp: cannot create render target from IDXGISwapChain"));
	
	_texture = GETexture(context, (ID3D11Texture2D*)back_buffer);
	
	back_buffer->Release();
}

Render::DX11RenderTarget::DX11RenderTarget(Core::GraphicsContext* context, GETexture texture)
	: _targetView(nullptr)
	, _context(context)
	, _texture(std::move(texture))
{
	GEAssert(_texture.is_render_target())
		.abort(TEXT("RenderTarget.cpp: texture passed in arguments is not a render target."));
	GEAssert(context->device->CreateRenderTargetView(_texture.texture(), nullptr, &_targetView))
		.abort(TEXT("RenderTarget.cpp: cannot create render target from texture"));
}

Render::DX11RenderTarget::DX11RenderTarget(Core::GraphicsContext* context, Surface texture_resolution)
	: _targetView(nullptr)
	, _context(context)
	, _texture(context, texture_resolution, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET)
{
	GEAssert(context->device->CreateRenderTargetView(_texture.texture(), nullptr, &_targetView))
		.abort(TEXT("RenderTarget.cpp: cannot create render target"));
}

Render::DX11RenderTarget::DX11RenderTarget(Core::GraphicsContext* context, ITexture2DDesc texture_desc)
	: _targetView(nullptr)
	, _context(context)
	, _texture(context,texture_desc)
{
	GEAssert(context->device->CreateRenderTargetView(_texture.texture(), nullptr, &_targetView))
		.abort(TEXT("RenderTarget.cpp: cannot create render target"));
}

Render::DX11RenderTarget::DX11RenderTarget(Core::GraphicsContext* context)
	: _targetView(nullptr)
	, _context(context)
	, _texture(context)
{}

Render::DX11RenderTarget::DX11RenderTarget(DX11RenderTarget&& other) noexcept
	: _targetView(other._targetView)
	, _context(other._context)
	, _texture(std::move(other._texture))
	, clear_color(other.clear_color)
{
	other._targetView = nullptr;
	other._context = nullptr;
	other._texture = GETexture(_context);
}

Render::DX11RenderTarget::~DX11RenderTarget()
{
	if (_targetView)
		_targetView->Release();
}

Render::DX11RenderTarget& Render::DX11RenderTarget::operator=(DX11RenderTarget&& other) noexcept
{
	if (_targetView)
		_targetView->Release();

	_context = other._context;
	clear_color = other.clear_color;
	_texture = std::move(other._texture);
	_targetView = other._targetView;

	return *this;
}

Core::GraphicsContext* Render::DX11RenderTarget::get_context()
{
	return _context;
}

ID3D11RenderTargetView* Render::DX11RenderTarget::get_view()
{
	return _targetView;
}

ID3D11Resource* Render::DX11RenderTarget::get_resource()
{
	return _texture.texture();
}

Render::GETexture* Render::DX11RenderTarget::get_texture()
{
	return &_texture;
}

void Render::DX11RenderTarget::bind(ID3D11DepthStencilView* stencil) const
{
	const auto num = _targetView == nullptr ? 0 : 1;
	_context->context->OMSetRenderTargets(num, _targetView == nullptr ? nullptr : &_targetView, stencil);
}

void Render::DX11RenderTarget::clear(Color4XM color) const
{
	auto float_color = color.to_float4();

	if (_targetView != nullptr)
		_context->context->ClearRenderTargetView(_targetView, (FLOAT*)&float_color);
}

void Render::DX11RenderTarget::clear(Color3XM color) const
{
	auto float_color = Color4XM(color).to_float4();
	
	if(_targetView != nullptr)
		_context->context->ClearRenderTargetView(_targetView, (FLOAT*)&float_color);
}

void Render::DX11RenderTarget::clear() const
{
	clear(clear_color);
}
