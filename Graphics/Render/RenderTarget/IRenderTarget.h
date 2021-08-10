#pragma once
#include <d3d11.h>

#include "../d3d/Buffer/Texture.h"

struct Color3;

namespace Render
{
	class __declspec(dllexport) IRenderTarget
	{
	protected:
		ID3D11RenderTargetView* _targetView;
		Core::GraphicsContext* _context;
		Texture _texture;

		IRenderTarget(Core::GraphicsContext* context);
	public:
		// create render target from texture. Texture must have RenderTarget bind flag
		IRenderTarget(Core::GraphicsContext* context, Texture texture);
		// create render target from empty texture
		IRenderTarget(Core::GraphicsContext* context, Surface texture_resolution);

		ID3D11Resource* get_resource();
		Texture* get_texture();

		void bind(ID3D11DepthStencilView* stencil = nullptr) const;
		void clear(Color3 color);

		void release();
	};
}
