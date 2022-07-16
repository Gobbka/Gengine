#pragma once
#include "Ecs/Ecs.h"
#include "Que/IPass/Passer.h"
#include "../Render/Common/Texture.h"


namespace Render
{
	struct PointLightComponent;

	class __declspec(dllexport) Scene
	{
		ECS::World* _world;
		GEGraphics* _graphics;
		ECS::Entity* _main_camera;
		Passer _render_pipeline;
	public:
		bool active = true;

		Passer& renderPipeline();

		ECS::Entity* getMainCamera();
		void setMainCamera(ECS::Entity*);

		void registerSystem(ECS::EntitySystem*system);

		ECS::Entity* createEntity(ECS::Entity*parent=nullptr);
		ECS::Entity* createCamera(GERenderTarget* target);
		template<typename Component>
		ECS::Entity* instantiate(Component&component);
		template<typename Component>
		ECS::Entity* instantiate();
		ECS::Entity* createModel(GETexture*texture, GETexture*normals=nullptr);
		ECS::Entity* create_point_light(PointLightComponent light);
		ECS::Entity* create_direction_light();
		
		ECS::World* world() const { return _world; }
		
		Scene(GEGraphics*graphics);
		void destroy() const;
	};

	template <typename Component>
	ECS::Entity* Scene::instantiate(Component& component)
	{
		auto* ent = createEntity();
		ent->assign<Component>(component);
		return ent;
	}

	template <typename Component>
	ECS::Entity* Scene::instantiate()
	{
		auto* ent = createEntity();
		ent->assign<Component>();
		return ent;
	}
}
