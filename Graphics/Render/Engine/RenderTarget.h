#pragma once
#include <d3d11.h>

#include "../d3d/Bindable.h"

struct Color3;

namespace Core {
	class GraphicsContext;
}

namespace Render {
	class Texture;

	class RenderTarget
	{
		ID3D11RenderTargetView* _targetView;
		Core::GraphicsContext* _context;
	public:
		RenderTarget(Core::GraphicsContext* context, IDXGISwapChain* swap);
		RenderTarget(Core::GraphicsContext* context, Texture* texture);

		void bind(ID3D11DepthStencilView* stencil=nullptr) const;
		void clear(Color3 color);
	};
}
