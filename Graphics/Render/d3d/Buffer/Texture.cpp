﻿#include "Texture.h"
#include "../../Engine/Camera.h"
#include "../../../Graphics/Material/Material.h"

ID3D11Texture2D* Render::Texture::texture()
{
	return _texture;
}

Render::Texture::Texture(Core::GraphicsContext* engine,Material material)
	: Bindable(engine)
{
	
	D3D11_TEXTURE2D_DESC texture_desc;
	texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texture_desc.Width = material.width();
	texture_desc.Height = material.height();
	texture_desc.MipLevels = 1;
	texture_desc.ArraySize = 1;
	texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texture_desc.SampleDesc = { 1,0 };
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SHADER_RESOURCE_VIEW_DESC rvDesc;
	rvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rvDesc.Texture2D.MipLevels = texture_desc.MipLevels;
	rvDesc.Texture2D.MostDetailedMip = texture_desc.MipLevels - 1;
	rvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
	
	D3D11_SUBRESOURCE_DATA sb{material.pSysMem(),(UINT)material.width() * 4,0};
	
	assert(SUCCEEDED(engine->device->CreateTexture2D(&texture_desc, &sb, &_texture)));

	assert(SUCCEEDED(engine->device->CreateShaderResourceView(_texture, &rvDesc, &_resource)));
}

void Render::Texture::bind()
{
	_engine->context->PSSetShaderResources(0, 1, &_resource);
}

char* Render::Texture::get_data(size_t* lpsize)
{
	D3D11_MAPPED_SUBRESOURCE mp;
	
	_engine->context->Map(_texture, 0, D3D11_MAP_READ, 0, &mp);
	
	_engine->context->Unmap(_texture, 0);

	return nullptr;
}
