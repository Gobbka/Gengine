#include "Texture.h"
#include "../../Engine/D3DEngine.h"

Render::Texture::Texture(D3DEngine* engine,Surface texture_surface, void* texrute_ptr)
	: Bindable(engine)
{

	static const Color3 gokba[] = { {1,1,0,},{1,1,0},{1,0,0},{1,0,0} };
	
	D3D11_TEXTURE2D_DESC texture_desc;
	texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texture_desc.Width = 2;
	texture_desc.Height = 2;
	texture_desc.MipLevels = 1;
	texture_desc.ArraySize = 1;
	texture_desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	texture_desc.SampleDesc = { 1,0 };
	texture_desc.CPUAccessFlags = 0;
	texture_desc.MiscFlags = 0;
	texture_desc.Usage = D3D11_USAGE_DEFAULT;
	
	D3D11_SUBRESOURCE_DATA sb{gokba,2*sizeof(Color3),0};
	
	assert(SUCCEEDED(engine->device()->CreateTexture2D(&texture_desc, &sb, &_texture)));

	assert(SUCCEEDED(engine->device()->CreateShaderResourceView(_texture, nullptr, &_resource)));
		
}

void Render::Texture::bind()
{
	_engine->context()->PSSetShaderResources(0, 1, &_resource);
}
