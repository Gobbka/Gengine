#include "UIManager.h"

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
		auto* camera = context->get_main_camera()->get<Render::Camera>().get_ptr();

		auto resolution = camera->get_view_resolution();
		auto* gcontext = context->get_context();
		gcontext->matrix_buffer.data.VPMatrix = DirectX::XMMatrixScaling(1.f / (resolution.width / 2), 1.f / (resolution.height / 2), 1.f);
		gcontext->matrix_buffer.update();

		gcontext->control_buffer.data.offset = Vector2(-1, 1);
		gcontext->control_buffer.data.opacity = 1.f;
		gcontext->control_buffer.update();
		
		auto* mask_engine = camera->get_mask_engine();
		Render::DrawEvent2D event(camera,nullptr);

		mask_engine->get_discardState()->bind(0);
		
		context->worldspace()->each<UI::InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<UI::InteractiveForm>form)
			{
				event.layer = form.get_ptr();
				event.set_alpha(1.f);

				form->update();
				form->render(&event);
			});

		mask_engine->clear_buffer();
	}
};

UI::UIManager::UIManager()
	: _cursor(0, 0)
{
	_animator.start();
}

UI::UIManager* UI::UIManager::instance()
{
	static auto* instance = new UIManager();
	return instance;
}

ECS::Entity* UI::UIManager::create_layer(Core::GraphicsContext* gfx)
{
	auto* ent = gfx->worldspace()->create();
	auto handle = ent->assign<InteractiveForm>(gfx, &_cursor);
	return ent;
}

void UI::UIManager::register_to(Core::GraphicsContext* context)
{
	context->get_passer()->add_pass(new DrawUIPass(), Render::PassStep::overlay);
}

UI::Animator* UI::UIManager::animator()
{
	return &_animator;
}

void UI::UIManager::on_lbmouse_down()
{
	for (auto* form : _forms)
		if (form->on_lbmouse_down() == Interaction::EventStatus::handled)
			return;
}

void UI::UIManager::on_lbmouse_up()
{
	for (auto* form : _forms)
		if (form->on_lbmouse_up() == Interaction::EventStatus::handled)
			return;
}

void UI::UIManager::on_mouse_scroll(short direction)
{
	for (auto* form : _forms)
		if (form->on_mouse_scroll(direction) == Interaction::EventStatus::handled)
			return;
}

void UI::UIManager::on_mouse_move(int mx, int my)
{
	_cursor = Position2(mx, my);
	
	for (auto iteration = _forms.size(); iteration --> 0;)
	{
		if (_forms[iteration]->on_mouse_move(mx,my) == Interaction::EventStatus::handled)
		{
			return;
		}
	}
}

void UI::UIManager::on_db_click()
{
	for (auto iteration = _forms.size(); iteration-- > 0;)
	{
		if (_forms[iteration]->on_db_click() == Interaction::EventStatus::handled)
		{
			return;
		}
	}
}
