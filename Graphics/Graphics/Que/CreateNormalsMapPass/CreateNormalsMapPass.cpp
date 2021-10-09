#include "CreateNormalsmapPass.h"
#include "../../../Graphics.h"
#include "../../../Render/Engine/Camera.h"
#include "../../Components/MeshRenderer.h"
#include "../../../IGContext.h"
#include "../../../Render/d3d/Buffer/ConstantBuffer.h"
#include "../../Components/NormalsRenderTarget.h"

void Render::CreateNormalsMapPass::execute(Core::GraphicsContext* context)
{
	auto* gcontext = context->get_context();

	context->main_scene->world()->each<NormalsRenderTarget,Camera>([&](ECS::Entity* ent, ECS::ComponentHandle<NormalsRenderTarget> nrt,ECS::ComponentHandle<Camera> cam)
		{
			gcontext->set_pixel_shader(context->shader_collection.get<PixelShader>(L"d3d11\\normals_ps.cso"));
			nrt->bind();
			// do stuff here
			
			auto world_matrix = cam->world_to_screen_matrix();
			context->main_scene->world()->each<MeshRenderer>([&](ECS::Entity* ent, ECS::ComponentHandle<MeshRenderer>component)
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