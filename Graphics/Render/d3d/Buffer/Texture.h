#pragma once
#include "../Bindable.h"
#include <d3d11.h>

#include "../../../Graphics/IBuffers/ITexture2D.h"

struct Surface;

namespace Render {
	class Material;

	class __declspec(dllexport) Texture : public ITexture2D
	{
	private:
		Core::GraphicsContext* _context;
		
		D3D11_TEXTURE2D_DESC get_desc();

		ID3D11Texture2D* _texture;
		ID3D11ShaderResourceView* _resource;
		UINT _width;
		UINT _height;
	public:
		ID3D11Texture2D* texture();

		Texture(Core::GraphicsContext* context, Surface resolution, UINT bind_flags = D3D11_BIND_SHADER_RESOURCE,DXGI_FORMAT format =DXGI_FORMAT_R8G8B8A8_UNORM);
		Texture(Core::GraphicsContext* context, Material material);
		Texture(Core::GraphicsContext* context, ID3D11Texture2D* texture);
		Texture(Core::GraphicsContext* context);

		void bind() override;

		bool is_render_target() override;
		bool is_shader_resource() override;
		
		char* get_data(size_t* lpsize=nullptr) override;
		
		void copy_to(Texture* target);
		void copy_to(ID3D11Resource* target);

		unsigned width() override { return _width; }
		unsigned height() override { return _height; }
	};
}
