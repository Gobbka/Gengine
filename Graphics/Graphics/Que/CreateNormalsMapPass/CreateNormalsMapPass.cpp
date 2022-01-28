#include "CreateNormalsmapPass.h"
#include "../../../Graphics.h"
#include "../../Camera.h"
#include "../../Components/MeshRenderer.h"
#include "../../../Render/Common/IGContext.h"
#include "../../Components/LightViewer.h"

void Render::CreateNormalsMapPass::execute(Scene* scene)
{
	auto* gcontext = _context->get_context();
	auto* commander = _context->commander;
	auto* world = scene->world();

	gcontext->debug_message("CreateNormalMapPass executed");
	commander->nm_begin();
	commander->render_begin();

	world->each<LightViewer, Camera>([&](ECS::Entity* ent, ECS::ComponentHandle<LightViewer> nrt, ECS::ComponentHandle<Camera> cam)
		{
			nrt->normals_map.bind();
			nrt->normals_map.clear();

			gcontext->set_mask_engine(cam->get_mask_engine());
			commander->bind_camera_matrix(cam.get_ptr());

			world->each<MeshRenderer>([&](ECS::Entity* ent, ECS::ComponentHandle<MeshRenderer>component)
				{
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

						commander->draw_mesh(mesh,component->transform.get_world_matrix());
					}
				});
		});
}

