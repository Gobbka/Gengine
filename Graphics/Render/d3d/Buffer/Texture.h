#pragma once
#include <d3d11.h>

#include "../../../Graphics/IBuffers/ITexture2D.h"

namespace Core
{
	class GraphicsContext;
}

struct Surface;

namespace Render {
	class Material;

	class __declspec(dllexport) Texture : public ITexture2D
	{
	private:
		Core::GraphicsContext* _context;
		
		D3D11_TEXTURE2D_DESC get_desc() const;

		ID3D11Texture2D* _texture;
		ID3D11ShaderResourceView* _resource;
		UINT _width;
		UINT _height;
	public:
		ID3D11Texture2D* texture() const;

		Texture(Core::GraphicsContext* context, Surface resolution, UINT bind_flags = D3D11_BIND_SHADER_RESOURCE,DXGI_FORMAT format =DXGI_FORMAT_R8G8B8A8_UNORM);
		Texture(Core::GraphicsContext* context, Material& material);
		Texture(Core::GraphicsContext* context, ID3D11Texture2D* texture);
		Texture(Core::GraphicsContext* context, ITexture2DDesc texture);
		Texture(Core::GraphicsContext* context);
		Texture(Texture&& move) noexcept;
		~Texture();

		Texture& operator=(Texture&& other) noexcept;

		ITexture2DDesc get_texture_desc() const;

		void bind() override;

		bool is_render_target() override;
		bool is_shader_resource() override;
		
		char* get_data(size_t* lpsize=nullptr) override;
		
		void copy_to(Texture* target) const;
		void copy_to(ID3D11Resource* target) const;

		unsigned width() override { return _width; }
		unsigned height() override { return _height; }
	};
}
