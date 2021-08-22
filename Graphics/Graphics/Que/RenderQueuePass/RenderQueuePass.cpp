#include "RenderQueuePass.h"
#include "../../../Render/Engine/Camera.h"
#include "../../../Graphics.h"
#include "../../Components/ColorComponent.h"
#include "../../Components/TextureComponent.h"

void Render::ClearPass::execute(Core::GraphicsContext* context)
{
	context->worldspace()->each<Camera>([](ECS::Entity* entity, ECS::ComponentHandle<Camera>camera)
		{
			camera->clear();
		});
}

void Render::RenderQueuePass::render_model(ECS::ComponentHandle<Camera> camera,ECS::ComponentHandle<Model> model, DirectX::XMMATRIX matrix)
{
	_matrix_buffer.data.VPMatrix = DirectX::XMMatrixTranspose(
		matrix
	);
	_matrix_buffer.update();

	camera->view(model.get_ptr());
}

void Render::RenderQueuePass::render_camera_3d(ECS::ComponentHandle<Camera> camera, ECS::World* world)
{
	auto world_to_screen = camera->world_to_screen_matrix();

	_control_buffer.data.offset = Position2{ 0,0 };
	_control_buffer.update();
	auto* sprite_engine = camera->graphics_context()->get_sprite_engine();

	sprite_engine->begin_color_mode();
	world->each<Model, ColorComponent>([&](ECS::Entity* ent, ECS::ComponentHandle<Model> model, ECS::ComponentHandle<ColorComponent>color)
		{
			auto modelMatrix = model->transform.get_world_matrix();
			render_model(camera, model, modelMatrix * world_to_screen);
		}
	);

	sprite_engine->begin_sprite_mode();
	world->each<Model, TextureComponent>([&](ECS::Entity* ent, ECS::ComponentHandle<Model> model, ECS::ComponentHandle<TextureComponent>texture)
		{
			sprite_engine->bind_texture(texture->texture);

			auto modelMatrix = model->transform.get_world_matrix();
			render_model(camera, model, modelMatrix * world_to_screen);
		}
	);
}

void Render::RenderQueuePass::render_camera_2d(ECS::ComponentHandle<Camera> camera)
{
	// on 2d draw
	auto resolution = camera->get_view_resolution();
	_matrix_buffer.data.VPMatrix = DirectX::XMMatrixScaling(1.f / (resolution.width / 2), 1.f / (resolution.height / 2), 1.f);
	_matrix_buffer.update();

	_control_buffer.data.offset = Vector2(-1, 1);
	_control_buffer.data.opacity = 1.f;
	_control_buffer.update();

	camera->render2d();
}

inline void Render::RenderQueuePass::render_camera(ECS::ComponentHandle<Camera> camera, ECS::World* world)
{
	camera->bind();

	if (camera->options()->render_3d)
		render_camera_3d(camera, world);
	render_camera_2d(camera);
}

Render::RenderQueuePass::RenderQueuePass(Core::GraphicsContext* context)
	: _matrix_buffer(context,0),
	_control_buffer(context,1, (UINT)(CBBindFlag::CBBindFlag_vs | CBBindFlag::CBBindFlag_ps))
{
	
}

void Render::RenderQueuePass::execute(Core::GraphicsContext* context)
{
	// € думаю стоит сделать следующую реализацию
	// camera->bind();
	// TechniquePasses->execute();
	// DrawPass3D->execute();
	// DrawPass2D->execute();
	_matrix_buffer.bind();
	_control_buffer.bind();
	
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
