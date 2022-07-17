﻿#include "Scene.h"

#include "Camera.h"
#include "../Graphics/Components/DirectionLightComponent.h"
#include "Components/MeshRenderer.h"
#include "Components/GameEntityComponent.h"
#include "Components/PointLightComponent.h"

Render::Passer& Render::Scene::renderPipeline()
{
	return _render_pipeline;
}

ECS::Entity* Render::Scene::getMainCamera()
{
	return _main_camera;
}

void Render::Scene::setMainCamera(ECS::Entity* cam)
{
	_main_camera = cam;
}

void Render::Scene::registerSystem(ECS::EntitySystem* system)
{
	_world->registerSystem(system);
}


ECS::Entity* Render::Scene::createEntity(ECS::Entity* parent)
{
	auto* ent = _world->create();
	ent->assign<Core::GameEntityComponent>(parent);
	return ent;
}

ECS::Entity* Render::Scene::createCamera(GERenderTarget* target)
{
	auto* ent = createEntity();
	
	ent->assign<Camera>(_graphics,target);

	return ent;
}

ECS::Entity* Render::Scene::createModel(GETexture* texture, GETexture* normals)
{
	auto* ent = createEntity();
	ent->assign<MeshRenderer>(texture,normals);

	return ent;
}

ECS::Entity* Render::Scene::create_point_light(PointLightComponent light)
{
	auto* ent = createEntity();
	ent->assign<PointLightComponent>(light);

	return ent;
}

ECS::Entity* Render::Scene::create_direction_light()
{
	auto ent = createEntity();
	ent->assign<DirectionLightComponent>(_graphics);
	return ent;
}

void Render::Scene::tick(float delta_time) const
{
	_world->tick(delta_time);
}

ECS::Entity* Render::Scene::getEntityById(size_t id) const
{
	return _world->getById(id);
}

void Render::Scene::destroyEntity(size_t id) const
{
	_world->destroy(
		getEntityById(id)
	);
}

void Render::Scene::destroyEntity(ECS::Entity* ent) const
{
	_world->destroy(ent);
}

Render::Scene::Scene(GEGraphics* graphics)
	: _world(ECS::World::createWorld())
	, _graphics(graphics)
	, _main_camera(nullptr)
{
}

Render::Scene::~Scene()
{
	_world->destroyWorld();
	delete _world;
}
