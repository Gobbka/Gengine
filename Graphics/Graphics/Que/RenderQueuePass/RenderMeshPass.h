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
		Core::GraphicsContext* _context;
		void execute() override;
	public:
		ClearPass(Core::GraphicsContext* context)
			: _context(context)
		{}
	};
	
	class __declspec(dllexport) RenderMeshPass : public IPass
	{
		Core::GraphicsContext* _context;

		void render_model(ECS::ComponentHandle<Camera> camera,ECS::ComponentHandle<MeshRenderer> model,DirectX::XMMATRIX VPMatrix);
		inline void render_camera(ECS::ComponentHandle<Camera> camera, ECS::World* world);
		inline void execute_scene(Render::Scene* scene);
	public:
		RenderMeshPass(Core::GraphicsContext* context);

		void execute() override;
	};
}
