#include "DrawSkyboxPass.h"
#include "../../../Graphics.h"
#include "../../Components/SkyboxComponent.h"
#include "../../../IGContext.h"
#include "../../../Render/Engine/Camera.h"

void Render::DrawSkyboxPass::execute()
{
	auto* gcontext = _context->get_context();

	for (const auto* scene : _context->scenes)
	{
		if (!scene->active)
			continue;
		auto* world = scene->world();

		world->each<Camera, SkyboxComponent>([&](ECS::Entity*, ECS::ComponentHandle<Camera>cam, ECS::ComponentHandle<SkyboxComponent>skybox)
			{
				cam->bind();

				world->each<SkyboxComponent>([](ECS::Entity* ent, ECS::ComponentHandle<SkyboxComponent> plight)
					{

					});
			});

		gcontext->set_shader_resource((Texture*)nullptr, 1);
	}
}
