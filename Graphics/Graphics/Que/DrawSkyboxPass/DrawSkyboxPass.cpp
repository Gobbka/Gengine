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
	auto* commander = _context->commander;
	gcontext->debug_message("DrawSkyboxPass executed");
	auto old_rasterizer = gcontext->get_rasterizer();

	gcontext->set_rasterizer(_skybox_rasterizer);
	gcontext->set_pixel_shader(_context->shader_collection.get<PixelShader>(L"d3d11\\texture_ps.cso"));

	commander->render_begin();

	auto* world = scene->world();

	world->each<Camera, SkyboxComponent>([&](ECS::Entity*, ECS::ComponentHandle<Camera>cam, ECS::ComponentHandle<SkyboxComponent>skybox)
		{
			cam->bind();

			auto vp_matrix = cam->rotation_matrix() * cam->projection_matrix();
			auto model_matrix = DirectX::XMMatrixTranslation(-.5f, .5f, -.5f);
			commander->bind_camera(cam.get_ptr(), vp_matrix);

			gcontext->set_shader_resource(skybox->sky_texture, 0);

			commander->draw_mesh(_skybox_cube,model_matrix);
		});

	gcontext->set_rasterizer(old_rasterizer);
}

Render::DrawSkyboxPass::DrawSkyboxPass(GEGraphics* context)
	: _context(context)
	, _skybox_cube(Cube::make_independent(context,Position3::null(),1))
	, _skybox_rasterizer(context->get_device()->create_rasterizer(RasterizerDesc(true)))
{}
