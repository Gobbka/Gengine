#pragma once
#include <DirectXMath.h>

#include "../IPass/IPass.h"
#include "../../Scene.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class MeshRenderer;
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

		void render_model(ECS::ComponentHandle<Camera> camera,ECS::ComponentHandle<MeshRenderer> model,DirectX::XMMATRIX VPMatrix);
		inline void render_camera(ECS::ComponentHandle<Camera> camera, ECS::World* world);
		inline void execute_scene(Render::Scene* scene);
	public:
		RenderQueuePass(Core::GraphicsContext* context);

		void execute(Core::GraphicsContext* context) override;
	};
}
