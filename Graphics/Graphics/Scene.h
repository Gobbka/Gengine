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
		ECS::Entity* _main_camera;
	public:
		bool active = true;

		ECS::Entity* get_main_camera();
		void set_main_camera(ECS::Entity*);

		ECS::Entity* create_entity(ECS::Entity*parent=nullptr);
		ECS::Entity* create_camera(RenderTarget* target);
		template<typename Component>
		ECS::Entity* instantiate(Component&component);
		template<typename Component>
		ECS::Entity* instantiate();
		ECS::Entity* create_model();
		ECS::Entity* create_direction_light();
		
		__forceinline ECS::World* world() const { return _world; }
		
		Scene(Core::GraphicsContext*context);
		void destroy() const;
	};

	template <typename Component>
	ECS::Entity* Scene::instantiate(Component& component)
	{
		auto* ent = create_entity();
		ent->assign<Component>(component);
		return ent;
	}

	template <typename Component>
	ECS::Entity* Scene::instantiate()
	{
		auto* ent = create_entity();
		ent->assign<Component>();
		return ent;
	}
}
