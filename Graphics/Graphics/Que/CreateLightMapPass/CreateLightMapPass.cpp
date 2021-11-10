#include "CreateLightMapPass.h"
#include "../../../Render/I3DObject/Cube/Cube.h"
#include "../../../Graphics.h"
//#include "../../../IGContext.h"
//#include "../../../Render/Engine/Camera.h"
//#include "../../Components/LightViewer.h"
//#include "../../Components/PointLightComponent.h"

void Render::CreateLightMapPass::execute(Scene*scene)
{
	//auto* gcontext = _context->get_context();
	//
	//for (const auto* scene : _context->scenes)
	//{
	//	if (!scene->active)
	//		continue;
	//	auto* world = scene->world();

	//	world->each<Camera, LightViewer>([&](ECS::Entity*, ECS::ComponentHandle<Camera>cam, ECS::ComponentHandle<LightViewer>lview)
	//	{
	//		lview->light_map.clear();
	//		lview->light_map.bind();

	//		gcontext->set_shader_resource(cam->get_mask_engine(),0);
	//		gcontext->set_shader_resource(&lview->normals_map,1);

	//		world->each<PointLightComponent>([](ECS::Entity* ent, ECS::ComponentHandle<PointLightComponent> plight)
	//		{

	//		});
	//	});

	//	gcontext->set_shader_resource((Texture*)nullptr, 1);
	//}
}

Render::CreateLightMapPass::CreateLightMapPass(Core::GraphicsContext* context)
	: _point_light_cube(Cube::make_independent(context,Position3::null(),1))
{
	_context = context;
}
