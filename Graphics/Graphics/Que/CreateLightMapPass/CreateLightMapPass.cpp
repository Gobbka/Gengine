#include "CreateLightMapPass.h"
#include "../../../Render/I3DObject/Cube/Cube.h"
#include "../../../Graphics.h"
//#include "../../../IGContext.h"
//#include "../../../Render/Engine/Camera.h"
//#include "../../Components/LightViewer.h"

void Render::CreateLightMapPass::execute()
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
	//		gcontext->set_shader_resource(cam->get_mask_engine());

	//		world->each<PointLightComponent>([](ECS::Entity* ent, ECS::ComponentHandle<PointLightComponent> plight)
	//		{

	//		});
	//	});
	//}
}

Render::CreateLightMapPass::CreateLightMapPass(Core::GraphicsContext* context)
	: _point_light_cube(Cube::make_independent(context,Position3::null(),1))
{
	_context = context;
}
