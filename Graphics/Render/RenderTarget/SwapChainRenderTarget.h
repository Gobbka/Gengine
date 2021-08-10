#pragma once
#include "IRenderTarget.h"

namespace Render
{
	class SwapChainRenderTarget : public IRenderTarget
	{
	public:
		SwapChainRenderTarget(Core::GraphicsContext* context, IDXGISwapChain* swap_chain);
	};

}
