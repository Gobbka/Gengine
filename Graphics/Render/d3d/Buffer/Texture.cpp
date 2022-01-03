#include "Texture.h"
#include "../../../Graphics.h"
#include "Logger/Logger.h"

D3D11_TEXTURE2D_DESC Render::Texture::get_desc() const
{
	D3D11_TEXTURE2D_DESC desc;
	_texture->GetDesc(&desc);
	return desc;
}

ID3D11Texture2D* Render::Texture::texture() const
{
	return _texture;
}

Render::Texture::Texture(Core::GraphicsContext* context, Surface resolution, UINT bind_flags, DXGI_FORMAT format)
	: _context(context)
	, _texture(nullptr)
	, _resource(nullptr)
{
	D3D11_TEXTURE2D_DESC texture_desc;
	texture_desc.BindFlags = bind_flags;
	texture_desc.Width = _width = (UINT)resolution.width;
	texture_desc.Height = _height = (UINT)resolution.height;
	texture_desc.MipLevels = 1;
	texture_desc.ArraySize = 1;
	texture_desc.Format = format;
	texture_desc.SampleDesc = { 1,0 };
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;
	
	D3D11_SHADER_RESOURCE_VIEW_DESC rvDesc;
	rvDesc.Format = DXGI_FORMAT_UNKNOWN;
	rvDesc.Texture2D.MipLevels = texture_desc.MipLevels;
	rvDesc.Texture2D.MostDetailedMip = texture_desc.MipLevels - 1;
	rvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;

	GEAssert(_context->device->CreateTexture2D(&texture_desc, nullptr, &_texture))
		.abort(TEXT("Texture.cpp: cannot create texture"));

	GEAssert(_context->device->CreateShaderResourceView(_texture, &rvDesc, &_resource))
		.abort(TEXT("Texture.cpp: cannot create shader resource view"));
}

Render::Texture::Texture(Core::GraphicsContext* engine,Material& material)
	: _context(engine)
	, _texture(nullptr)
	, _resource(nullptr)
{
	D3D11_TEXTURE2D_DESC texture_desc;
	texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texture_desc.Width = _width = (UINT)material.width();
	texture_desc.Height = _height = (UINT)material.height();
	texture_desc.MipLevels = 1;
	texture_desc.ArraySize = 1;
	texture_desc.Format = material.format;
	texture_desc.SampleDesc= { 1,0 };
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SHADER_RESOURCE_VIEW_DESC rvDesc;
	rvDesc.Format = DXGI_FORMAT_UNKNOWN;
	rvDesc.Texture2D.MipLevels = texture_desc.MipLevels;
	rvDesc.Texture2D.MostDetailedMip = texture_desc.MipLevels - 1;
	rvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;

	GEAssert(engine->device->CreateTexture2D(&texture_desc, nullptr, &_texture))
		.abort(TEXT("Texture.cpp: cannot create texture2d from material"));

	engine->context->UpdateSubresource(_texture, 0, nullptr, material.pSysMem(), (UINT)material.width() * 4,0);

	GEAssert(engine->device->CreateShaderResourceView(_texture, &rvDesc, &_resource))
		.abort(TEXT("Texture.cpp: cannot create shader resource view from material texture"));
}

Render::Texture::Texture(Core::GraphicsContext* context, ID3D11Texture2D* texture)
	: _context(context)
	, _texture(texture)
	, _resource(nullptr)
{
	D3D11_TEXTURE2D_DESC desc;
	_texture->GetDesc(&desc);
	_width = desc.Width;
	_height = desc.Height;
}

Render::Texture::Texture(Core::GraphicsContext* context, ITexture2DDesc texture)
	: _context(context)
	, _texture(nullptr)
	, _resource(nullptr)
{
	D3D11_TEXTURE2D_DESC texture_desc;
	texture_desc.BindFlags = texture.bind_flag;
	texture_desc.Width = _width = texture.width;
	texture_desc.Height = _height = texture.height;
	texture_desc.MipLevels = 1;
	texture_desc.ArraySize = 1;
	texture_desc.Format = texture.format;
	texture_desc.SampleDesc = { 1,0 };
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SHADER_RESOURCE_VIEW_DESC rvDesc;
	rvDesc.Format = DXGI_FORMAT_UNKNOWN;
	rvDesc.Texture2D.MipLevels = texture_desc.MipLevels;
	rvDesc.Texture2D.MostDetailedMip = texture_desc.MipLevels - 1;
	rvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;

	GEAssert(context->device->CreateTexture2D(&texture_desc, nullptr, &_texture))
		.abort(TEXT("Texture.cpp: Cannot create texture2d from ITexture2DDesc"));

	auto slice = texture.stride;
	if (slice == 0)
		slice = (unsigned)texture.width * 4;

	if(texture.pSysMem)
		context->context->UpdateSubresource(_texture, 0, nullptr, texture.pSysMem, slice, 0);

	GEAssert(context->device->CreateShaderResourceView(_texture, &rvDesc, &_resource))
		.abort(TEXT("Texture.cpp: cannot create shader resurce view from texture from ITexture2DDesc"));
}

Render::Texture::Texture(Core::GraphicsContext* context)
	: _context(context)
	, _texture(nullptr)
	, _resource(nullptr)
	, _width(0)
	, _height(0)
{}

Render::Texture::Texture(Texture&& move) noexcept
	: _context(move._context)
	, _texture(move._texture)
	, _resource(move._resource)
	, _width(move._width)
	, _height(move._height)
{
	move._resource = nullptr;
	move._texture = nullptr;
}

Render::Texture::Texture(Texture& other)
	: _context(other._context)
	, _texture(nullptr)
	, _resource(nullptr)
	, _width(other.width())
	, _height(other._height)
{
	const auto d3ddesc = other.get_desc();
	_context->device->CreateTexture2D(&d3ddesc, nullptr, &_texture);
	other.copy_to(this);

	if(other._resource && _texture)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC rv_desc;
		other._resource->GetDesc(&rv_desc);
		_context->device->CreateShaderResourceView(_texture, &rv_desc, &_resource);
	}
}

Render::Texture::~Texture()
{
	if (_texture)
		_texture->Release();
	if (_resource)
		_resource->Release();
}

Render::Texture& Render::Texture::operator=(Texture&& other) noexcept
{
	if (_texture && _texture != other._texture)
		_texture->Release();
	if (_resource && _resource != other._resource)
		_resource->Release();

	_width = other._width;
	_height = other._height;
	_resource = other._resource;
	_texture = other._texture;
	_context = other._context;

	other._resource = nullptr;
	other._texture = nullptr;

	return*this;
}

Render::ITexture2DDesc Render::Texture::get_texture_desc() const
{
	D3D11_TEXTURE2D_DESC textDesc;
	_texture->GetDesc(&textDesc);

	return ITexture2DDesc{
		textDesc.Usage == D3D11_USAGE_DEFAULT ? ITexture2DDesc::Usage::DEFAULT : ITexture2DDesc::Usage::STAGING,
		textDesc.BindFlags,
		textDesc.Format,
		textDesc.Width,
		textDesc.Height,
		0,
		0,
		nullptr
	};
}

Surface Render::Texture::resolution() const
{
	return { (float)_width,(float)_height };
}

void Render::Texture::bind(UINT slot)
{
	_context->context->PSSetShaderResources(slot, 1, &_resource);
}

bool Render::Texture::is_render_target()
{
	return get_desc().BindFlags & D3D11_BIND_RENDER_TARGET;
}

bool Render::Texture::is_shader_resource()
{
	return get_desc().BindFlags & D3D11_BIND_SHADER_RESOURCE;
}

char* Render::Texture::get_data(size_t* lpsize)
{
	D3D11_MAPPED_SUBRESOURCE mp;
	
	_context->context->Map(_texture, 0, D3D11_MAP_READ, 0, &mp);
	
	_context->context->Unmap(_texture, 0);

	return nullptr;
}

void Render::Texture::copy_to(Texture* target) const
{
	_context->context->CopyResource(target->_texture, _texture);
}

void Render::Texture::copy_to(ID3D11Resource* target) const
{
	_context->context->CopyResource(target, _texture);
}
