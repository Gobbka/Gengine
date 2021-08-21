#include "RenderQueuePass.h"
#include "../../../Render/Engine/Camera.h"
#include "../../../Graphics.h"

void Render::ClearPass::execute(Core::GraphicsContext* context)
{
	context->worldspace()->each<Camera>([](ECS::Entity* entity, ECS::ComponentHandle<Camera>camera)
		{
			camera->clear();
		});
}

void Render::RenderQueuePass::execute(Core::GraphicsContext* context)
{
	// € думаю стоит сделать следующую реализацию
	// camera->bind();
	// TechniquePasses->execute();
	// DrawPass3D->execute();
	// DrawPass2D->execute();
	
	auto* main_camera = context->get_main_camera();
	ECS::ComponentHandle<Camera> hMainCamera;
	context->worldspace()->each<Camera>([&](ECS::Entity* entity, ECS::ComponentHandle<Camera>camera)
		{
			if(main_camera == entity)
			{
				hMainCamera = camera;
			}else
			{
				camera->render();
			}
		});
	if(hMainCamera.isValid())
	{
		hMainCamera->render();
	}
}
