#include "RenderMeshPass.h"

#include "../../Components/MeshRenderer.h"
#include "../../../Render/Engine/Camera.h"
#include "../../../Graphics.h"
#include "../../../IGContext.h"
#include "../../Mesh.h"

void Render::ClearPass::execute(Core::GraphicsContext* context)
{
	for (auto* scene : context->scenes) {
		scene->world()->each<Camera>([](ECS::Entity* entity, ECS::ComponentHandle<Camera>camera)
		{
			camera->clear();
		});
	}
}

void Render::RenderMeshPass::render_model(ECS::ComponentHandle<Camera> camera,ECS::ComponentHandle<MeshRenderer> model, DirectX::XMMATRIX VPMatrix)
{	
	auto* gcontext = _context->get_context();
	auto model_matrix = model->transform.get_world_matrix();
	gcontext->matrix_buffer.data.MVPMatrix = DirectX::XMMatrixTranspose(model_matrix * VPMatrix);
	gcontext->matrix_buffer.data.ModelMatrix = DirectX::XMMatrixTranspose(model_matrix);
	gcontext->matrix_buffer.update();
	
	for(auto mesh : model->meshes)
	{
		mesh.index_buffer->bind();
		mesh.buffer->bind();
		gcontext->set_topology(mesh.topology);
		gcontext->draw_indexed(mesh.index_buffer->get_size());
	}
}

inline void Render::RenderMeshPass::render_camera(ECS::ComponentHandle<Camera> camera, ECS::World* world)
{
	camera->bind();

	auto world_to_screen = camera->world_to_screen_matrix();
	auto* sprite_engine = camera->graphics_context()->get_sprite_engine();

	sprite_engine->begin_sprite_mode(true);
	world->each<MeshRenderer>([&](ECS::Entity* ent, ECS::ComponentHandle<MeshRenderer> model)
		{
			sprite_engine->bind_texture(model->texture);
			render_model(camera, model, world_to_screen);
		}
	);
}

inline void Render::RenderMeshPass::execute_scene(Render::Scene* scene)
{
	auto main_camera_id = scene->get_main_camera()->getEntityId();
	ECS::ComponentHandle<Camera> hMainCamera;
	auto* world = scene->world();

	world->each<Camera>([&](ECS::Entity* entity, ECS::ComponentHandle<Camera>camera)
		{
			if (main_camera_id == entity->getEntityId())
			{
				hMainCamera = camera;
			}
			else
			{
				render_camera(camera, world);
			}
		});
	if (hMainCamera.isValid())
	{
		render_camera(hMainCamera, world);
	}
}

Render::RenderMeshPass::RenderMeshPass(Core::GraphicsContext* context)
{
	_context = context;
}

void Render::RenderMeshPass::execute(Core::GraphicsContext* context)
{
	auto* gcontext = _context->get_context();
	gcontext->set_topology(PrimitiveTopology::TRIANGLELIST);
	gcontext->matrix_buffer.bind();
	gcontext->control_buffer.bind();

	for (auto* scene : context->scenes) {

		if (!scene->active||scene == context->main_scene)
			continue;

		execute_scene(scene);
	}

	execute_scene(context->main_scene);
}
