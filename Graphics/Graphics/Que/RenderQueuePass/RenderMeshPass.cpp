#include "RenderMeshPass.h"

#include "../../Components/MeshRenderer.h"
#include "../../Camera.h"
#include "../../../Graphics.h"
#include "../../../Render/Common/IGContext.h"
#include "../../../Render/Common/Texture.h"
#include "../../Mesh.h"
#include "../../Components/LightViewer.h"

void Render::ClearPass::execute(Scene*scene)
{
	_context->get_context()->debug_message("ClearPass executed");

	scene->world()->each<Camera>([](ECS::Entity* entity, ECS::ComponentHandle<Camera>camera)
		{
			camera->clear();
		});
}

inline void Render::RenderMeshPass::render_camera(ECS::ComponentHandle<Camera> camera,ECS::ComponentHandle<LightViewer>lview, ECS::World* world)
{
	auto* commander = _context->commander;

	commander->render_begin();
	commander->bind_camera(camera.get_ptr());
	_context->dss_collection[(DSBitSet)DepthStencilUsage::depth_equal].bind();

	auto* sprite_engine = camera->get_graphics()->get_sprite_engine();

	sprite_engine->begin_sprite_mode(true);
	sprite_engine->bind_texture(lview->normals_map.get_texture(), 1);
	world->each<MeshRenderer>([&](ECS::Entity* ent, ECS::ComponentHandle<MeshRenderer> model)
		{
			sprite_engine->bind_texture(model->texture,0);
			
			for(Mesh mesh : model->meshes)
			{
				commander->draw_mesh(mesh, model->transform.get_world_matrix());
			}
		}
	);
}

inline void Render::RenderMeshPass::execute_scene(Scene* scene)
{
	auto main_camera_id = scene->getMainCamera()->getEntityId();
	ECS::ComponentHandle<Camera> hMainCamera;
	ECS::ComponentHandle<LightViewer> hLightViewer;
	auto* world = scene->world();

	world->each<Camera,LightViewer>([&](ECS::Entity* entity, ECS::ComponentHandle<Camera>camera,ECS::ComponentHandle<LightViewer>lview)
		{
			if (main_camera_id == entity->getEntityId())
			{
				hMainCamera = camera;
				hLightViewer = lview;
			}
			else
			{
				render_camera(camera,lview, world);
			}
		});
	if (hMainCamera.isValid())
	{
		render_camera(hMainCamera, hLightViewer, world);
	}
}

Render::RenderMeshPass::RenderMeshPass(GEGraphics* context)
	: _context(context)
{
}

void Render::RenderMeshPass::execute(Scene*scene)
{
	auto* gcontext = _context->get_context();
	gcontext->debug_message("RenderMeshPass");

	_context->get_sprite_engine()->bind_texture(nullptr, 1);
	execute_scene(scene);
}
