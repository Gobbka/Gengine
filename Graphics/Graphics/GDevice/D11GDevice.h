#pragma once
#include <d3d11.h>

#include "../../IGDevice.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class __declspec(dllexport) D11GDevice final : public IGDevice
	{
		ID3D11Device* _device;
		Core::GraphicsContext* _gfx;
	public:
		D11GDevice(ID3D11Device* device,Core::GraphicsContext*context);
		
		ECS::Entity* create_camera(RenderTarget* target) override;
		ECS::Entity* create_model() override;
	};
}
