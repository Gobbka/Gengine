#pragma once
#include "../Bindable.h"
#include <d3d11.h>

struct Surface;

namespace Render {
	class Texture : Bindable
	{
	public:
		ID3D11Texture2D* _texture;
		ID3D11ShaderResourceView* _resource;
	public:
		Texture(D3DEngine* engine, Surface texture_surface,void* texrute_ptr);

		void bind() override;
	};
}
