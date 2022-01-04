#pragma once
#include <d3d11.h>
#include "../Common/Texture.h"
#include "Types/Types.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	class __declspec(dllexport) DX11RenderTarget
	{
		ID3D11RenderTargetView* _targetView;
		Core::GraphicsContext* _context;
		GETexture _texture;
	public:
		Color4XM clear_color = Color4XM(0, 0, 0,1.f);
		
		// create render target from IDXGISwapChain
		DX11RenderTarget(Core::GraphicsContext* context, IDXGISwapChain* swap);
		// create render target from texture. Texture must have RenderTarget bind flag
		DX11RenderTarget(Core::GraphicsContext* context, GETexture texture);
		// create render target from empty texture
		DX11RenderTarget(Core::GraphicsContext* context, Surface texture_resolution);
		DX11RenderTarget(Core::GraphicsContext* context, ITexture2DDesc texture_desc);

		DX11RenderTarget(Core::GraphicsContext* context);

		DX11RenderTarget(DX11RenderTarget&& other) noexcept;
		~DX11RenderTarget();

		DX11RenderTarget& operator=(DX11RenderTarget&& other) noexcept;

		Core::GraphicsContext* get_context();
		ID3D11RenderTargetView* get_view();
		ID3D11Resource* get_resource();
		GETexture* get_texture();

		void bind(ID3D11DepthStencilView* stencil=nullptr) const;
		void clear(Color4XM color) const;
		void clear(Color3XM color) const;
		void clear() const;
	};
}
