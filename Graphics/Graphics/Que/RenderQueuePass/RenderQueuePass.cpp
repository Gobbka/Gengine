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
	context->worldspace()->each<Camera>([](ECS::Entity* entity, ECS::ComponentHandle<Camera>camera)
		{
			camera->render();
		});
}
