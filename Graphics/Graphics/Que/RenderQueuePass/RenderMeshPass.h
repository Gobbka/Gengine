#pragma once
#include <DirectXMath.h>

#include "../IPass/IPass.h"
#include "../../Scene.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	struct LightViewer;
	class MeshRenderer;
	class Camera;
	class VertexShader;
	class PixelShader;

	class ClearPass : public IPass
	{
		Core::GraphicsContext* _context;
		void execute(Scene*scene) override;
	public:
		ClearPass(Core::GraphicsContext* context)
			: _context(context)
		{}
	};
	
	class __declspec(dllexport) RenderMeshPass : public IPass
	{
		Core::GraphicsContext* _context;

		void render_model(ECS::ComponentHandle<Camera> camera,ECS::ComponentHandle<MeshRenderer> model,DirectX::XMMATRIX VPMatrix) const;
		inline void render_camera(ECS::ComponentHandle<Camera> camera,ECS::ComponentHandle<LightViewer> lview, ECS::World* world);
		inline void execute_scene(Render::Scene* scene);
	public:
		RenderMeshPass(Core::GraphicsContext* context);

		void execute(Scene*scene) override;
	};
}
