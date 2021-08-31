#include "UIContext.h"

#include <iostream>

#include "IGContext.h"
#include "Render/Engine/Camera.h"
#include "InteractiveForm.h"
#include "Render/Engine/MaskEngine.h"
#include "Render/Events/RenderEvent.h"

class DrawUIPass : public Render::IPass
{
public:
	void execute(Core::GraphicsContext* context) override
	{
		auto* camera = context->active_scene->get_main_camera()->get<Render::Camera>().get_ptr();

		auto resolution = camera->get_view_resolution();
		auto* gcontext = context->get_context();
		gcontext->set_topology(PrimitiveTopology::TRIANGLESTRIP);
		gcontext->matrix_buffer.data.VPMatrix = DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicLH(resolution.width,resolution.height,0.0,1.f) * DirectX::XMMatrixTranslation(-1,1,0)
		);
		gcontext->matrix_buffer.update();

		gcontext->control_buffer.data.opacity = 1.f;
		gcontext->control_buffer.update();
		
		auto* mask_engine = camera->get_mask_engine();
		Render::DrawEvent2D event(camera,nullptr);

		mask_engine->get_discardState()->bind(0);
		
		context->active_scene->world()->each<UI::InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<UI::InteractiveForm>form)
			{
				if (form->hidden())
					return;
				event.layer = form.get_ptr();
				event.set_alpha(1.f);

				form->update();
				form->render(&event);
			});

		mask_engine->clear_buffer();
	}
};

ECS::Entity* UI::UIContext::create_layer()
{
	auto* ent = _gfx->active_scene->world()->create();
	auto handle = ent->assign<InteractiveForm>(_gfx, &_cursor);
	handle->show();
	return ent;
}

UI::UIContext::UIContext(Core::GraphicsContext* gfx)
	: WinIntEventHandler(),
	_cursor(0,0)
{
	_gfx = gfx;
	_animator.start();

	gfx->get_passer()->add_pass(new DrawUIPass(), Render::PassStep::overlay);
}

UI::Animator* UI::UIContext::animator()
{
	return &_animator;
}

void UI::UIContext::on_lbmouse_down()
{
	_gfx->active_scene->world()->each<InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<InteractiveForm> form)
		{
			form->on_lbmouse_down();
		});
}

void UI::UIContext::on_lbmouse_up()
{
	_gfx->active_scene->world()->each<InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<InteractiveForm> form)
		{
			form->on_lbmouse_up();
		});
}

void UI::UIContext::on_mouse_scroll(short direction)
{
	_gfx->active_scene->world()->each<InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<InteractiveForm> form)
		{
			form->on_mouse_scroll(direction);
		});
}

void UI::UIContext::on_mouse_move(int mx, int my)
{
	_cursor = Position2(mx, my);

	_gfx->active_scene->world()->each<InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<InteractiveForm> form)
		{
			form->on_mouse_move(mx, my);
		});
}

void UI::UIContext::on_db_click()
{
	_gfx->active_scene->world()->each<InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<InteractiveForm> form)
		{
			form->on_db_click();
		});
}
