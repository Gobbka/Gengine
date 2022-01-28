#include "CreateShadowMapPass.h"

#include "../../Components/MeshRenderer.h"
#include "../../../Graphics.h"
#include "../../../Render/Common/IGContext.h"
#include "../../../Graphics/Components/DirectionLightComponent.h"
#include "../../Mesh.h"


void Render::CreateShadowMapPass::execute(Scene*scene)
{
	auto* gcontext = _context->get_context();
	auto* commander = _context->commander;
	gcontext->debug_message("CreateShadowMapPass");
	auto* old_ps = gcontext->get_pixel_shader();

	gcontext->set_pixel_shader(nullptr);
	
	scene->world()->each<DirectionLightComponent>([&](ECS::Entity* ent, ECS::ComponentHandle<DirectionLightComponent> handle)
		{
			handle->bind();
			handle->mask_engine->clear_buffer();

			// do stuff here

			auto world_matrix = handle->world_to_screen_matrix();
			scene->world()->each<MeshRenderer>([&](ECS::Entity* ent, ECS::ComponentHandle<MeshRenderer>component)
				{
					auto modelMatrix = component->transform.get_world_matrix();

					commander->bind_camera(nullptr, world_matrix);

					for (Mesh mesh : component->meshes)
					{
						commander->draw_mesh(mesh,modelMatrix);
					}
				});
		});

	// clean up
	gcontext->set_pixel_shader(old_ps);
}
