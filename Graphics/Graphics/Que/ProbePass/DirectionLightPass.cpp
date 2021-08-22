#include "DirectionLightPass.h"

#include "../../../Graphics.h"
#include "../../../Render/Light/DirectionLight.h"

Render::DirectionLightPass::DirectionLightPass(Core::GraphicsContext* context)
	: _matrix_buffer(context)
	//_control_buffer(context)
{
	
}

void Render::DirectionLightPass::execute(Core::GraphicsContext* context)
{
	auto* world = context->worldspace();
	_matrix_buffer.bind();
	
	//world->each<DirectionLight>([&](ECS::Entity* ent, ECS::ComponentHandle<DirectionLight> hLight)
	//	{
	//		auto world_to_screen = hLight->world_to_screen_matrix();

	//		world->each<Model>([&](ECS::Entity* modelEnt, ECS::ComponentHandle<Model>hModel)
	//			{

	//			});
	//	
	//		hLight->create_shadowmap();
	//	});
}
