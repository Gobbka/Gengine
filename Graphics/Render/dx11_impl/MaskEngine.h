#pragma once
#include <d3d11.h>
#include "../Common/Bindable.h"
#include "../Common/Texture.h"

namespace Render
{
	enum class MaskEngineUsage
	{
		Depth,
		DepthStencil,
	};
	
	class __declspec(dllexport) DX11MaskEngine
	{
		Core::GraphicsContext* _context;
		GETexture _buffer;
		ID3D11DepthStencilView* _view;
		DX11RenderTarget* _target;
	public:
		DX11MaskEngine(DX11RenderTarget* target, MaskEngineUsage usage = MaskEngineUsage::DepthStencil);
		explicit DX11MaskEngine(Core::GraphicsContext* context,Surface resolution, MaskEngineUsage usage = MaskEngineUsage::DepthStencil);

		void clear_buffer() const;

		auto* get_gfx() { return _context; };

		auto get_view() { return _view; }
		GETexture* get_texture();
	};
}
