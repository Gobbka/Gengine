#pragma once
#include <DirectXMath.h>
#include "../IPass/IPass.h"
#include "../../Scene.h"

namespace Render
{
	struct LightViewer;
	class MeshRenderer;
	class Camera;

	class ClearPass : public IPass
	{
		Core::DX11Graphics* _context;
		void execute(Scene*scene) override;
	public:
		ClearPass(Core::DX11Graphics* context)
			: _context(context)
		{}
	};
	
	class __declspec(dllexport) RenderMeshPass : public IPass
	{
		Core::DX11Graphics* _context;

		void render_model(ECS::ComponentHandle<Camera> camera,ECS::ComponentHandle<MeshRenderer> model,DirectX::XMMATRIX VPMatrix) const;
		inline void render_camera(ECS::ComponentHandle<Camera> camera,ECS::ComponentHandle<LightViewer> lview, ECS::World* world);
		inline void execute_scene(Render::Scene* scene);
	public:
		RenderMeshPass(Core::DX11Graphics* context);

		void execute(Scene*scene) override;
	};
}
