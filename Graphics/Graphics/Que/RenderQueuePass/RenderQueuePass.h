#pragma once
#include "../IPass/IPass.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class VertexShader;
	class PixelShader;
	class MaskEngine;
	class RenderTarget;

	class __declspec(dllexport) RenderQueuePass : IPass
	{

	public:
		void execute(Core::GraphicsContext* context) override;
	};
}
