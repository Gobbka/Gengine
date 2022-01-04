#pragma once
#include <d3d11.h>
#include "Types/Types.h"

namespace Core
{
	class DX11Graphics;
}

namespace Render
{
	struct ITexture2DDesc;
	class Material;

	class __declspec(dllexport) DX11Texture
	{
		Core::DX11Graphics* _context;
		
		D3D11_TEXTURE2D_DESC get_desc() const;

		ID3D11Texture2D* _texture;
		ID3D11ShaderResourceView* _resource;
		UINT _width;
		UINT _height;
	public:
		ID3D11Texture2D* texture() const;

		DX11Texture(Core::DX11Graphics* context, Surface resolution, UINT bind_flags = D3D11_BIND_SHADER_RESOURCE,DXGI_FORMAT format =DXGI_FORMAT_R8G8B8A8_UNORM);
		DX11Texture(Core::DX11Graphics* context, Material& material);
		DX11Texture(Core::DX11Graphics* context, ID3D11Texture2D* texture);
		DX11Texture(Core::DX11Graphics* context, ITexture2DDesc texture);
		DX11Texture(Core::DX11Graphics* context);
		DX11Texture(DX11Texture&& move) noexcept;
		DX11Texture(DX11Texture& other);
		~DX11Texture();

		DX11Texture& operator=(DX11Texture&& other) noexcept;

		ITexture2DDesc get_texture_desc() const;
		Surface resolution() const;

		void bind(UINT slot=0) ;

		bool is_render_target() ;
		bool is_shader_resource() ;
		
		char* get_data(size_t* lpsize=nullptr) ;
		
		void copy_to(DX11Texture* target) const;
		void copy_to(ID3D11Resource* target) const;

		unsigned width()  { return _width; }
		unsigned height() { return _height; }
	};
}
