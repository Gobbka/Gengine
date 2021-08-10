#include "Texture.h"
#include "../../Engine/Camera.h"
#include "../../../Graphics/Material/Material.h"

D3D11_TEXTURE2D_DESC Render::Texture::get_desc()
{
	D3D11_TEXTURE2D_DESC desc;
	_texture->GetDesc(&desc);
	return D3D11_TEXTURE2D_DESC(desc);
}

ID3D11Texture2D* Render::Texture::texture()
{
	return _texture;
}

Render::Texture::Texture(Core::GraphicsContext* context, Surface resolution, UINT bind_flags, DXGI_FORMAT format)
	: _context(context)
{
	D3D11_TEXTURE2D_DESC texture_desc;
	texture_desc.BindFlags = bind_flags;
	texture_desc.Width = _width = resolution.width;
	texture_desc.Height = _height = resolution.height;
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

	D3D11_SUBRESOURCE_DATA sb{ new char[resolution.width * resolution.height * 4],resolution.width * 4,0 };

	assert(SUCCEEDED(_context->device->CreateTexture2D(&texture_desc, &sb, &_texture)));

	assert(SUCCEEDED(_context->device->CreateShaderResourceView(_texture, &rvDesc, &_resource)));
}

Render::Texture::Texture(Core::GraphicsContext* engine,Material material)
	: _context(engine)
{
	D3D11_TEXTURE2D_DESC texture_desc;
	texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texture_desc.Width = _width = material.width();
	texture_desc.Height = _height = material.height();
	texture_desc.MipLevels = 1;
	texture_desc.ArraySize = 1;
	texture_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	texture_desc.SampleDesc = { 1,0 };
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SHADER_RESOURCE_VIEW_DESC rvDesc;
	rvDesc.Format = DXGI_FORMAT_UNKNOWN;
	rvDesc.Texture2D.MipLevels = texture_desc.MipLevels;
	rvDesc.Texture2D.MostDetailedMip = texture_desc.MipLevels - 1;
	rvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
	
	D3D11_SUBRESOURCE_DATA sb{material.pSysMem(),(UINT)material.width() * 4,0};
	
	assert(SUCCEEDED(engine->device->CreateTexture2D(&texture_desc, &sb, &_texture)));

	assert(SUCCEEDED(engine->device->CreateShaderResourceView(_texture, &rvDesc, &_resource)));
}

Render::Texture::Texture(Core::GraphicsContext* context, ID3D11Texture2D* texture)
	: _context(context)
{
	_texture = texture;
	D3D11_TEXTURE2D_DESC desc;
	_texture->GetDesc(&desc);
	_width = desc.Width;
	_height = desc.Height;
}

Render::Texture::Texture(Core::GraphicsContext* context)
	: _context(context)
{
}

void Render::Texture::bind()
{
	_context->context->PSSetShaderResources(0, 1, &_resource);
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

void Render::Texture::copy_to(Texture* target)
{
	_context->context->CopyResource(target->_texture, _texture);
}

void Render::Texture::copy_to(ID3D11Resource* target)
{
	_context->context->CopyResource(target, _texture);
}
