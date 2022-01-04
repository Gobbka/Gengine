#include "CreateLightMapPass.h"
#include "../../I3DObject/Cube/Cube.h"
#include "../../../Graphics.h"
#include "../../../Render/Common/IGContext.h"
#include "../../Camera.h"
#include "../../Components/LightViewer.h"
#include "../../Components/PointLightComponent.h"
#include "../../Components/MeshRenderer.h"


void Render::CreateLightMapPass::execute(Scene*scene)
{
	auto* world = scene->world();

	auto* gcontext = _context->get_context();
	gcontext->debug_message("CreateLightMapPass executed");
	_light_struct.bind();
	auto* old_ps = gcontext->get_pixel_shader();

	gcontext->set_pixel_shader(
		_context->shader_collection.get<PixelShader>(L"d3d11\\point_light_ps.cso")
	);
	
	world->each<Camera, LightViewer>([&](ECS::Entity*, ECS::ComponentHandle<Camera>cam, ECS::ComponentHandle<LightViewer>lview)
	{
		lview->light_map.clear();
		lview->light_map.bind();

		gcontext->set_shader_resource(cam->get_mask_engine(),0);
		gcontext->set_shader_resource(&lview->normals_map,1);

		world->each<PointLightComponent>([&](ECS::Entity* ent, ECS::ComponentHandle<PointLightComponent> plight)
		{
			_light_struct.data.pos = plight->position;
			_light_struct.data.intensity = plight->intensity;
			_light_struct.update();

			world->each<MeshRenderer>([&](ECS::Entity* entity, ECS::ComponentHandle<MeshRenderer>rendered)
			{

			});
		});
	});

	gcontext->set_pixel_shader(old_ps);
}

Render::CreateLightMapPass::CreateLightMapPass(Core::GraphicsContext* context)
	: _light_struct(context,0,CBBindFlag_ps)
	, _point_light_cube(Cube::make_independent(context,Position3::null(),1))
	, _context(context)
{}
