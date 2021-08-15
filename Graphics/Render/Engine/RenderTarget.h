﻿#pragma once
#include <d3d11.h>

#include "../d3d/Bindable.h"
#include "../d3d/Buffer/Texture.h"

struct Color3;

namespace Core {
	class GraphicsContext;
}

namespace Render {
	class Texture;

	enum class RenderTargetUsage
	{
		null
	};
	
	class __declspec(dllexport) RenderTarget
	{
		ID3D11RenderTargetView* _targetView;
		Core::GraphicsContext* _context;
		Texture _texture;
	public:
		// create render target from IDXGISwapChain
		RenderTarget(Core::GraphicsContext* context, IDXGISwapChain* swap);
		// create render target from texture. Texture must have RenderTarget bind flag
		RenderTarget(Core::GraphicsContext* context, Texture texture);
		// create render target from empty texture
		RenderTarget(Core::GraphicsContext* context, Surface texture_resolution);

		RenderTarget(Core::GraphicsContext* context, RenderTargetUsage usage);
		
		
		ID3D11Resource* get_resource();
		Texture* get_texture();

		void bind(ID3D11DepthStencilView* stencil=nullptr) const;
		void clear(Color3 color);

		void release();
	};
}
