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

	class ClearPass : public IPass
	{
		void execute(Core::GraphicsContext* context) override;
	};
	
	class __declspec(dllexport) RenderQueuePass : public IPass
	{

	public:
		void execute(Core::GraphicsContext* context) override;
	};
}
