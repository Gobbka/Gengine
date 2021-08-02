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
	public:
		ID3D11Texture2D* texture();
		
		Texture(Core::GraphicsContext* engine, Material material);

		void bind() override;
	};
}
