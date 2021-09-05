#include "Scene.h"


#include "../Render/Engine/Camera.h"
#include "../Render/Light/DirectionLightComponent.h"
#include "../Render/Model/MeshContainerComponent.h"
#include "Components/GameEntityComponent.h"

ECS::Entity* Render::Scene::get_main_camera()
{
	return _main_camera;
}

void Render::Scene::set_main_camera(ECS::Entity* cam)
{
	_main_camera = cam;
}

ECS::Entity* Render::Scene::create_entity(ECS::Entity* parent)
{
	auto* ent = _world->create();
	ent->assign<Core::GameEntityComponent>(parent);
	return ent;
}

ECS::Entity* Render::Scene::create_camera(RenderTarget* target)
{
	auto* ent = create_entity();
	
	ent->assign<Camera>(_context,target);

	return ent;
}

ECS::Entity* Render::Scene::create_model()
{
	auto* ent = create_entity();
	ent->assign<MeshContainerComponent>();

	return ent;
}

ECS::Entity* Render::Scene::create_direction_light()
{
	auto ent = _world->create();
	ent->assign<DirectionLightComponent>(_context);
	return ent;
}

Render::Scene::Scene(Core::GraphicsContext* context)
{
	_world = ECS::World::createWorld();
	_main_camera = nullptr;
	_context = context;
}

void Render::Scene::destroy() const
{
	delete _world;
}
