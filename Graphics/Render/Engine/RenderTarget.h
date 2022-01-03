﻿#pragma once
#include <d3d11.h>
#include "../d3d/Buffer/Texture.h"
#include "Types/Types.h"

struct Color3XM;

namespace Core {
	class GraphicsContext;
}

namespace Render {
	struct ITexture2DDesc;
	class Texture;

	class __declspec(dllexport) RenderTarget
	{
		ID3D11RenderTargetView* _targetView;
		Core::GraphicsContext* _context;
		Texture _texture;
	public:
		Color4XM clear_color = Color4XM(0, 0, 0,1.f);
		
		// create render target from IDXGISwapChain
		RenderTarget(Core::GraphicsContext* context, IDXGISwapChain* swap);
		// create render target from texture. Texture must have RenderTarget bind flag
		RenderTarget(Core::GraphicsContext* context, Texture texture);
		// create render target from empty texture
		RenderTarget(Core::GraphicsContext* context, Surface texture_resolution);
		RenderTarget(Core::GraphicsContext* context, ITexture2DDesc texture_desc);

		RenderTarget(Core::GraphicsContext* context);

		RenderTarget(RenderTarget&& other) noexcept;
		~RenderTarget();

		RenderTarget& operator=(RenderTarget&& other) noexcept;

		Core::GraphicsContext* get_context();
		ID3D11RenderTargetView* get_view();
		ID3D11Resource* get_resource();
		Texture* get_texture();

		void bind(ID3D11DepthStencilView* stencil=nullptr) const;
		void clear(Color4XM color) const;
		void clear(Color3XM color) const;
		void clear() const;
	};
}
