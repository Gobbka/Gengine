﻿#pragma once
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
		Texture(D3DEngine* engine, Material material);

		void bind() override;
	};
}