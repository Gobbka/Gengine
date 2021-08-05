#pragma once
#include "../Bindable.h"
#include <d3d11.h>

struct Surface;

namespace Render {
	class Material;

	class __declspec(dllexport) Texture : Bindable
	{
	private:
		virtual UINT bind_flags() { return D3D11_BIND_SHADER_RESOURCE; }
		
	public:
		ID3D11Texture2D* _texture;
		ID3D11ShaderResourceView* _resource;
		UINT width;
		UINT height;
	public:
		ID3D11Texture2D* texture();

		Texture(Core::GraphicsContext* context, Surface resolution, UINT bind_flags = D3D11_BIND_SHADER_RESOURCE,DXGI_FORMAT format =DXGI_FORMAT_R8G8B8A8_UNORM);
		Texture(Core::GraphicsContext* context, Material material);
		Texture(Core::GraphicsContext* context, ID3D11Texture2D* texture);
		Texture(Core::GraphicsContext* context);
		
		void create_shader_resource();
		
		void bind() override;

		ID3D11Texture2D* get_texture();
		
		char* get_data(size_t* lpsize=nullptr);
		
		void copy_to(Texture* target);
		void copy_to(ID3D11Resource* target);
	};
}
