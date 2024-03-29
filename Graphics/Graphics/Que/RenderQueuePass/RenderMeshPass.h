#pragma once
#include "../IPass/IPass.h"
#include "../../Scene.h"

namespace Render
{
	struct LightViewer;
	class MeshRenderer;
	class Camera;

	class __declspec(dllexport) ClearPass : public IPass
	{
		GEGraphics* _context;
		void execute(Scene*scene) override;
	public:
		ClearPass(GEGraphics* context)
			: _context(context)
		{}
	};
	
	class __declspec(dllexport) RenderMeshPass : public IPass
	{
		GEGraphics* _context;

		inline void render_camera(ECS::ComponentHandle<Camera> camera,ECS::ComponentHandle<LightViewer> lview, ECS::World* world);
		inline void execute_scene(Scene* scene);
	public:
		RenderMeshPass(GEGraphics* context);

		void execute(Scene*scene) override;
	};
}
