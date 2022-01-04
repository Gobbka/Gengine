#include "DrawSkyboxPass.h"
#include "../../../Graphics.h"
#include "../../Components/SkyboxComponent.h"
#include "../../../Render/Common/IGContext.h"
#include "../../Camera.h"
#include "../../I3DObject/Cube/Cube.h"
#include "../../../Render/Common/IndexBuffer.h"

void Render::DrawSkyboxPass::execute(Scene*scene)
{
	auto* gcontext = _context->get_context();
	gcontext->debug_message("DrawSkyboxPass executed");
	auto old_rasterizer = gcontext->get_rasterizer();

	gcontext->set_rasterizer(_skybox_rasterizer);
	gcontext->set_topology(_skybox_cube.topology);
	gcontext->set_pixel_shader(_context->shader_collection.get<PixelShader>(L"d3d11\\texture_ps.cso"));

	_skybox_cube.buffer->bind();
	_skybox_cube.index_buffer->bind();

	auto* world = scene->world();

	world->each<Camera, SkyboxComponent>([&](ECS::Entity*, ECS::ComponentHandle<Camera>cam, ECS::ComponentHandle<SkyboxComponent>skybox)
		{
			cam->bind();

			auto vp_matrix = cam->rotation_matrix() * cam->projection_matrix();
			auto model_matrix = DirectX::XMMatrixTranslation(-.5f, .5f, -.5f);
			gcontext->matrix_buffer.data.ModelMatrix = DirectX::XMMatrixTranspose(model_matrix);
			gcontext->matrix_buffer.data.MVPMatrix = DirectX::XMMatrixMultiplyTranspose(model_matrix, vp_matrix);
			gcontext->matrix_buffer.update();

			gcontext->set_shader_resource(skybox->sky_texture, 0);
			gcontext->draw_indexed(_skybox_cube.index_buffer->get_size());
		});

	gcontext->set_rasterizer(old_rasterizer);
}

Render::DrawSkyboxPass::DrawSkyboxPass(Core::GraphicsContext* context)
	: _context(context)
	, _skybox_cube(Cube::make_independent(context,Position3::null(),1))
	, _skybox_rasterizer(context->get_device()->create_rasterizer(RasterizerDesc(true)))
{}
