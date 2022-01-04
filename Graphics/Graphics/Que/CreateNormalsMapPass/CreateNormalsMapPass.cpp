#include "CreateNormalsmapPass.h"
#include "../../../Graphics.h"
#include "../../../Render/Engine/Camera.h"
#include "../../Components/MeshRenderer.h"
#include "../../../Render/Common/IGContext.h"
#include "../../../Render/Common/IndexBuffer.h"
#include "../../../Render/d3d/Buffer/ConstantBuffer.h"
#include "../../Components/LightViewer.h"

void Render::CreateNormalsMapPass::execute(Scene* scene)
{
	auto* gcontext = _context->get_context();
	gcontext->debug_message("CreateNormalMapPass executed");
	_context->dss_collection[(DSBitSet)DepthStencilUsage::depth].bind();

	auto* world = scene->world();

	world->each<LightViewer, Camera>([&](ECS::Entity* ent, ECS::ComponentHandle<LightViewer> nrt, ECS::ComponentHandle<Camera> cam)
		{
			auto* normals_ps = _context->shader_collection.get<PixelShader>(L"d3d11\\normals_ps.cso");
			auto* normals_texture_ps = _context->shader_collection.get<PixelShader>(L"d3d11\\normals_texture_ps.cso");

			nrt->normals_map.bind();
			nrt->normals_map.clear();

			gcontext->set_mask_engine(cam->get_mask_engine());
			_context->dss_collection[(DSBitSet)DepthStencilUsage::depth].bind();
			// do stuff here
			auto* sprite_engine = _context->get_sprite_engine();
			auto world_matrix = cam->world_to_screen_matrix();
			world->each<MeshRenderer>([&](ECS::Entity* ent, ECS::ComponentHandle<MeshRenderer>component)
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

						if (component->normals)
						{
							sprite_engine->bind_texture(component->normals, 0);
							gcontext->set_pixel_shader(normals_texture_ps);
						}
						else
						{
							gcontext->set_pixel_shader(normals_ps);
						}
						gcontext->draw_indexed(mesh.index_buffer->get_size());
					}
				});
		});
}

