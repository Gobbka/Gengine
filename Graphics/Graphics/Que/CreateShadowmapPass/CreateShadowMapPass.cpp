#include "CreateShadowMapPass.h"

#include "../../Components/MeshRenderer.h"
#include "../../../Graphics.h"
#include "../../../IGContext.h"
#include "../../../Render/Engine/MaskEngine.h"
#include "../../../Render/Events/RenderEvent.h"
#include "../../../Render/Light/DirectionLightComponent.h"
#include "../../Mesh.h"


void Render::CreateShadowMapPass::execute(Core::GraphicsContext* context)
{
	auto* gcontext = context->get_context();
	auto* old_ps = gcontext->get_pixel_shader();

	gcontext->set_pixel_shader(nullptr);
	
	for (auto* scene : context->scenes) {
		if (!scene->active)
			continue;

		scene->world()->each<DirectionLightComponent>([&](ECS::Entity* ent, ECS::ComponentHandle<DirectionLightComponent> handle)
			{
				handle->bind();
				handle->get_mask_engine()->clear_buffer();

				// do stuff here

				auto world_matrix = handle->world_to_screen_matrix();
				scene->world()->each<MeshRenderer>([&](ECS::Entity* ent, ECS::ComponentHandle<MeshRenderer>component)
					{
						auto modelMatrix = component->transform.get_world_matrix();
						auto final_matrix = DirectX::XMMatrixMultiplyTranspose(modelMatrix, world_matrix);
						gcontext->matrix_buffer.data.MVPMatrix = final_matrix;
						gcontext->matrix_buffer.data.ModelMatrix = DirectX::XMMatrixTranspose(modelMatrix);
						gcontext->matrix_buffer.update();

						for (const auto mesh : component->meshes)
						{
							mesh.index_buffer->bind();
							mesh.buffer->bind();
							gcontext->set_topology(mesh.topology);
							gcontext->draw_indexed(mesh.index_buffer->get_size());
						}
					});
			});
	}

	// clean up
	gcontext->set_pixel_shader(old_ps);
}
