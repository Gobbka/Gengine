#pragma once
#include <d3d11.h>
#include "../d3d/Bindable.h"

struct Surface;

namespace Render {
	class RenderTarget;
	class WorldViewer;

	enum class StencilUsage : __int8
	{
		normal,
		write,
		mask,
	};

	enum class MaskEngineUsage
	{
		Depth,
		DepthStencil,
	};
	
	class __declspec(dllexport) MaskEngine
	{
	private:
		Core::GraphicsContext* _context;

		ID3D11Texture2D* _buffer;
		ID3D11DepthStencilView* _view;
		RenderTarget* _target;
	public:
		MaskEngine(RenderTarget* target, MaskEngineUsage usage = MaskEngineUsage::DepthStencil);
		explicit MaskEngine(Core::GraphicsContext* context,Surface resolution, MaskEngineUsage usage = MaskEngineUsage::DepthStencil);

		void clear_buffer() const;

		auto get_view() { return _view; }
	};
}
