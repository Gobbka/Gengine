#include "RenderQueuePass.h"
#include "../../../Render/Engine/Camera.h"
#include "../../../Graphics.h"
#include "../../../IGContext.h"
#include "../../Components/ColorComponent.h"
#include "../../Components/TextureComponent.h"

void Render::ClearPass::execute(Core::GraphicsContext* context)
{
	context->worldspace()->each<Camera>([](ECS::Entity* entity, ECS::ComponentHandle<Camera>camera)
		{
			camera->clear();
		});
}

void Render::RenderQueuePass::render_model(ECS::ComponentHandle<Camera> camera,ECS::ComponentHandle<Model> model, DirectX::XMMATRIX MVPMatrix)
{
	auto* gcontext = _context->get_context();
	
	gcontext->matrix_buffer.data.VPMatrix = DirectX::XMMatrixTranspose(MVPMatrix);
	gcontext->matrix_buffer.data.ModelMatrix = DirectX::XMMatrixTranspose(model->transform.get_world_matrix());
	gcontext->matrix_buffer.update();

	camera->view(model.get_ptr());
}

void Render::RenderQueuePass::render_camera_3d(ECS::ComponentHandle<Camera> camera, ECS::World* world)
{
	auto world_to_screen = camera->world_to_screen_matrix();
	auto* gcontext = _context->get_context();
	gcontext->control_buffer.data.offset = Position2{ 0,0 };
	gcontext->control_buffer.update();
	auto* sprite_engine = camera->graphics_context()->get_sprite_engine();

	sprite_engine->begin_color_mode();
	world->each<Model, ColorComponent>([&](ECS::Entity* ent, ECS::ComponentHandle<Model> model, ECS::ComponentHandle<ColorComponent>color)
		{
			auto modelMatrix = model->transform.get_world_matrix();
			render_model(camera, model, modelMatrix * world_to_screen);
		}
	);

	sprite_engine->begin_sprite_mode(true);
	world->each<Model, TextureComponent>([&](ECS::Entity* ent, ECS::ComponentHandle<Model> model, ECS::ComponentHandle<TextureComponent>texture)
		{
			sprite_engine->bind_texture(texture->texture);

			auto modelMatrix = model->transform.get_world_matrix();
			render_model(camera, model, modelMatrix * world_to_screen);
		}
	);
}

inline void Render::RenderQueuePass::render_camera(ECS::ComponentHandle<Camera> camera, ECS::World* world)
{
	camera->bind();

	if (camera->options()->render_3d)
		render_camera_3d(camera, world);
}

Render::RenderQueuePass::RenderQueuePass(Core::GraphicsContext* context)
{
	_context = context;
}

void Render::RenderQueuePass::execute(Core::GraphicsContext* context)
{
	// € думаю стоит сделать следующую реализацию
	// camera->bind();
	// TechniquePasses->execute();
	// DrawPass3D->execute();
	// DrawPass2D->execute();
	auto* gcontext = _context->get_context();
	gcontext->set_topology(PrimitiveTopology::TRIANGLELIST);
	gcontext->matrix_buffer.bind();
	gcontext->control_buffer.bind();
	
	auto* main_camera = context->get_main_camera();
	ECS::ComponentHandle<Camera> hMainCamera;
	auto world = context->worldspace();
	
	context->worldspace()->each<Camera>([&](ECS::Entity* entity, ECS::ComponentHandle<Camera>camera)
		{
			if(main_camera == entity)
			{
				hMainCamera = camera;
			}else
			{
				render_camera(camera, world);
			}
		});
	if(hMainCamera.isValid())
	{
		render_camera(hMainCamera, world);
	}
}
