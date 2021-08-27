#pragma once
#include "Ecs/Ecs.h"

namespace Core {
	class GraphicsContext;
}

namespace Render {
	class RenderTarget;
	class Camera;

	class __declspec(dllexport) Scene
	{
		ECS::World* _world;
		Core::GraphicsContext* _context;
		Camera* _main_camera;
	public:
		Camera* get_main_camera();
		void set_main_camera(Camera*);

		ECS::Entity* create_camera(RenderTarget* target);
		ECS::Entity* create_model();
		
		inline ECS::World* world() const { return _world; }
		
		Scene(Core::GraphicsContext*context);
		void destroy() const;
	};
}
