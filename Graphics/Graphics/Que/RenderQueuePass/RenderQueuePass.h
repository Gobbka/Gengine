#pragma once
#include <DirectXMath.h>
#include "../../../Render/Model/MeshContainerComponent.h"
#include "../IPass/IPass.h"
#include "Ecs/Ecs.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class Camera;
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
		Core::GraphicsContext* _context;
		
		void render_camera_3d(ECS::ComponentHandle<Camera> camera, ECS::World* world);

		void render_model(ECS::ComponentHandle<Camera> camera,ECS::ComponentHandle<MeshContainerComponent> model,DirectX::XMMATRIX VPMatrix);
		inline void render_camera(ECS::ComponentHandle<Camera> camera, ECS::World* world);
	public:
		RenderQueuePass(Core::GraphicsContext* context);
		
		void execute(Core::GraphicsContext* context) override;
	};
}
