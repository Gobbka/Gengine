#pragma once
#include "../Bindable.h"
#include <d3d11.h>

struct Surface;

namespace Render {
	class Material;

	class Texture : Bindable
	{
	public:
		ID3D11Texture2D* _texture;
		ID3D11ShaderResourceView* _resource;
		UINT width;
		UINT height;
	public:
		ID3D11Texture2D* texture();
		
		Texture(Core::GraphicsContext* engine, Material material);
		Texture(Core::GraphicsContext* context, ID3D11Texture2D* texture);

		void bind() override;

		char* get_data(size_t* lpsize=nullptr);
		void copy_to(Texture* target);
	};
}
