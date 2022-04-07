#include "Scene.h"

#include "Camera.h"
#include "../Graphics/Components/DirectionLightComponent.h"
#include "Components/MeshRenderer.h"
#include "Components/GameEntityComponent.h"
#include "Components/PointLightComponent.h"

Render::Passer& Render::Scene::render_pipeline()
{
	return _render_pipeline;
}

ECS::Entity* Render::Scene::get_main_camera()
{
	return _main_camera;
}

void Render::Scene::set_main_camera(ECS::Entity* cam)
{
	_main_camera = cam;
}

void Render::Scene::register_system(ECS::EntitySystem* system)
{
	_world->registerSystem(system);
}


ECS::Entity* Render::Scene::create_entity(ECS::Entity* parent)
{
	auto* ent = _world->create();
	ent->assign<Core::GameEntityComponent>(parent);
	return ent;
}

ECS::Entity* Render::Scene::create_camera(GERenderTarget* target)
{
	auto* ent = create_entity();
	
	ent->assign<Camera>(_graphics,target);

	return ent;
}

ECS::Entity* Render::Scene::create_model(GETexture* texture, GETexture* normals)
{
	auto* ent = create_entity();
	ent->assign<MeshRenderer>(texture,normals);

	return ent;
}

ECS::Entity* Render::Scene::create_point_light(PointLightComponent light)
{
	auto* ent = create_entity();
	ent->assign<PointLightComponent>(light);

	return ent;
}

ECS::Entity* Render::Scene::create_direction_light()
{
	auto ent = create_entity();
	ent->assign<DirectionLightComponent>(_graphics);
	return ent;
}

Render::Scene::Scene(GEGraphics* graphics)
	: _world(ECS::World::createWorld())
	, _graphics(graphics)
	, _main_camera(nullptr)
{
}

void Render::Scene::destroy() const
{
	delete _world;
}
