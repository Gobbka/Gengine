#include "UIContext.h"

#include <iostream>

#include "Graphics.h"
#include "IGContext.h"
#include "Render/Engine/Camera.h"
#include "InteractiveForm.h"
#include "Graphics/SpriteFont.h"
#include "Graphics/Components/TextComponent.h"
#include "Graphics/Que/IPass/IPass.h"
#include "Render/Engine/MaskEngine.h"
#include "Render/Events/RenderEvent.h"
#include <Render/d3d/Buffer/ConstantBuffer.h>

class DrawUIPass : public Render::IPass
{
	Core::GraphicsContext* _context;

public:
	void execute() override
	{
		auto* camera = _context->main_scene->get_main_camera()->get<Render::Camera>().get_ptr();
		camera->bind();

		auto resolution = camera->get_view_resolution();
		auto* gcontext = _context->get_context();
		gcontext->set_topology(PrimitiveTopology::TRIANGLESTRIP);
		gcontext->matrix_buffer.data.MVPMatrix = DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicLH(resolution.width,resolution.height,0.0,1.f) * DirectX::XMMatrixTranslation(-1,1,0)
		);
		gcontext->matrix_buffer.update();

		gcontext->control_buffer.data.opacity = 1.f;
		gcontext->control_buffer.update();
		
		auto* mask_engine = camera->get_mask_engine();
		Render::DrawEvent2D event(camera,nullptr);

		_context->dss_collection[(Render::DSBitSet)Render::DepthStencilUsage::stencil_mask].bind(0);
		
		_context->main_scene->world()->each<UI::InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<UI::InteractiveForm>form)
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

	DrawUIPass(Core::GraphicsContext*context)
		: _context(context)
	{}
};

class DrawTextPass : public Render::IPass
{
	Core::GraphicsContext* _context;

	void execute() override
	{
		auto* matrix = &_context->get_context()->matrix_buffer;

		auto resolution = _context->get_screen_resolution();
		auto worldMatrix = 
			DirectX::XMMatrixOrthographicLH(resolution.width, resolution.height, 0.0, 1.f) * 
			DirectX::XMMatrixTranslation(-1,1,0) // move count point to top-left corner
		;

		_context->main_scene->world()->each<Render::TextComponent>([&](ECS::Entity*, ECS::ComponentHandle<Render::TextComponent>comp)
			{
				matrix->data.MVPMatrix = DirectX::XMMatrixTranspose(
					DirectX::XMMatrixTranslation(0,-0,0) * 
					worldMatrix
				);
				matrix->update();

				_context->get_context()->set_topology(PrimitiveTopology::TRIANGLELIST);
				comp->vbuffer->bind();
				comp->ibuffer->bind();
				comp->font->font_texture->bind();

				_context->get_context()->draw_indexed(comp->ibuffer->get_size());
			});
	}

public:
	DrawTextPass(Core::GraphicsContext*context)
		: _context(context)
	{}
};

ECS::Entity* UI::UIContext::create_layer()
{
	auto* ent = _gfx->main_scene->world()->create();
	auto handle = ent->assign<InteractiveForm>(_gfx, &_cursor);
	handle->show();
	return ent;
}

UI::UIContext::UIContext(Core::GraphicsContext* gfx)
	: WinIntEventHandler(),
	_cursor(0,0)
{
	_gfx = gfx;

	gfx->get_passer()->add_pass(new DrawUIPass(gfx), Render::PassStep::overlay);
	gfx->get_passer()->add_pass(new DrawTextPass(gfx), Render::PassStep::overlay);
}

void UI::UIContext::on_lbmouse_down()
{
	_gfx->main_scene->world()->each<InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<InteractiveForm> form)
		{
			form->on_lbmouse_down();
		});
}

void UI::UIContext::on_lbmouse_up()
{
	_gfx->main_scene->world()->each<InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<InteractiveForm> form)
		{
			form->on_lbmouse_up();
		});
}

void UI::UIContext::on_mouse_scroll(short direction)
{
	_gfx->main_scene->world()->each<InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<InteractiveForm> form)
		{
			form->on_mouse_scroll(direction);
		});
}

void UI::UIContext::on_mouse_move(int mx, int my)
{
	_cursor = Position2(mx, my);

	_gfx->main_scene->world()->each<InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<InteractiveForm> form)
		{
			form->on_mouse_move(mx, my);
		});
}

void UI::UIContext::on_db_click()
{
	_gfx->main_scene->world()->each<InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<InteractiveForm> form)
		{
			form->on_db_click();
		});
}
