#include "CreateNormalsmapPass.h"
#include "../../../Graphics.h"
#include "../../Camera.h"
#include "../../Components/MeshRenderer.h"
#include "../../../Render/Common/IGContext.h"
#include "../../../Render/d3d/Buffer/ConstantBuffer.h"
#include "../../Components/LightViewer.h"

void Render::CreateNormalsMapPass::execute(Scene* scene)
{
	auto* gcontext = _context->get_context();
	auto* commander = _context->commander;
	auto* world = scene->world();

	gcontext->debug_message("CreateNormalMapPass executed");
	commander->nm_begin();

	world->each<LightViewer, Camera>([&](ECS::Entity* ent, ECS::ComponentHandle<LightViewer> nrt, ECS::ComponentHandle<Camera> cam)
		{
			nrt->normals_map.bind();
			nrt->normals_map.clear();

			gcontext->set_mask_engine(cam->get_mask_engine());

			// do stuff here
			auto world_matrix = cam->world_to_screen_matrix();
			world->each<MeshRenderer>([&](ECS::Entity* ent, ECS::ComponentHandle<MeshRenderer>component)
				{
					auto modelMatrix = component->transform.get_world_matrix();
					auto final_matrix = DirectX::XMMatrixMultiplyTranspose(modelMatrix, world_matrix);
					gcontext->matrix_buffer.data.MVPMatrix = final_matrix;
					gcontext->matrix_buffer.data.ModelMatrix = DirectX::XMMatrixTranspose(modelMatrix);
					gcontext->matrix_buffer.update();

					for (Mesh mesh : component->meshes)
					{
						if (component->normals)
						{
							commander->nm_texture_mode(component->normals);
						}
						else
						{
							commander->nm_solid_mode();
						}

						commander->draw_mesh(mesh);
					}
				});
		});
}

