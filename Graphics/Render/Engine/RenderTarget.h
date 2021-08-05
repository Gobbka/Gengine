#pragma once
#include <d3d11.h>

#include "../d3d/Bindable.h"
#include "../d3d/Buffer/Texture.h"

struct Color3;

namespace Core {
	class GraphicsContext;
}

namespace Render {
	class Texture;

	class __declspec(dllexport) RenderTarget
	{
		ID3D11RenderTargetView* _targetView;
		Core::GraphicsContext* _context;
		Texture _texture;
	public:
		RenderTarget(Core::GraphicsContext* context, IDXGISwapChain* swap);
		RenderTarget(Core::GraphicsContext* context, Texture texture);

		static RenderTarget* create_texture(Core::GraphicsContext* context);
		
		ID3D11Resource* get_resource();
		Texture* get_texture();

		void bind(ID3D11DepthStencilView* stencil=nullptr) const;
		void clear(Color3 color);

		void release();
	};
}
