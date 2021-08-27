#include "Scene.h"


#include "../Render/Engine/Camera.h"
#include "../Render/Model/MeshContainerComponent.h"

Render::Camera* Render::Scene::get_main_camera()
{
	return _main_camera;
}

void Render::Scene::set_main_camera(Camera*cam)
{
	_main_camera = cam;
}

ECS::Entity* Render::Scene::create_camera(RenderTarget* target)
{
	auto entt = _world->create();
	
	entt->assign<Camera>(_context,target);

	return entt;
}

ECS::Entity* Render::Scene::create_model()
{
	auto entt = _world->create();
	entt->assign<MeshContainerComponent>();

	return entt;
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
