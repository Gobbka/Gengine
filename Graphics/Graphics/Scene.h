#pragma once
#include "Ecs/Ecs.h"
#include "Que/IPass/Passer.h"
#include "../Render/Common/Texture.h"
struct PointLightComponent;

namespace Core {
	class GraphicsContext;
}

namespace Render {
	class Camera;

	class __declspec(dllexport) Scene
	{
		ECS::World* _world;
		Core::GraphicsContext* _context;
		ECS::Entity* _main_camera;
		Passer _render_pipeline;
	public:
		bool active = true;

		Passer& render_pipeline();

		ECS::Entity* get_main_camera();
		void set_main_camera(ECS::Entity*);

		void register_system(ECS::EntitySystem*system);

		ECS::Entity* create_entity(ECS::Entity*parent=nullptr);
		ECS::Entity* create_camera(GERenderTarget* target);
		template<typename Component>
		ECS::Entity* instantiate(Component&component);
		template<typename Component>
		ECS::Entity* instantiate();
		ECS::Entity* create_model(GETexture*texture, GETexture*normals=nullptr);
		ECS::Entity* create_point_light(PointLightComponent light);
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
