#include "UIContext.h"

#include <iostream>
#include "Graphics.h"
#include "IGContext.h"
#include "Render/Engine/Camera.h"
#include "InteractiveForm.h"
#include "Graphics/Components/TextComponent.h"
#include "Canvas/RenderEvent.h"
#include <Render/d3d/Buffer/ConstantBuffer.h>
#include "Canvas/Vertex2D.h"
#include "Render/d3d/Shader/VertexShader.h"

class DrawUIPass : public Render::IPass
{
	Core::GraphicsContext* _context;

public:
	void execute(Render::Scene*scene) override
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

		auto* old_ps = gcontext->get_pixel_shader();
		auto* old_vs = gcontext->get_vertex_shader();

		gcontext->set_pixel_shader(_context->shader_collection.get<Render::PixelShader>(L"d3d11\\canvas_ps.cso"));
		gcontext->set_vertex_shader(_context->shader_collection.get_vs(L"d3d11\\canvas_vs.cso"));

		scene->world()->each<UI::InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<UI::InteractiveForm>form)
			{
				if (form->hidden())
					return;
				event.layer = form->canvas();
				event.set_alpha(1.f);

				form->update();
				form->render(&event);
			});

		gcontext->set_pixel_shader(old_ps);
		gcontext->set_vertex_shader(old_vs);

		mask_engine->clear_buffer();
	}

	DrawUIPass(Core::GraphicsContext*context)
		: _context(context)
	{}
};

class DrawTextPass : public Render::IPass
{
	Core::GraphicsContext* _context;

	void execute(Render::Scene*scene) override
	{
		auto* matrix = &_context->get_context()->matrix_buffer;

		auto resolution = _context->get_screen_resolution();
		auto worldMatrix = 
			DirectX::XMMatrixOrthographicLH(resolution.width, resolution.height, 0.0, 1.f) * 
			DirectX::XMMatrixTranslation(-1,1,0) // move count point to top-left corner
		;

		scene->world()->each<Render::TextComponent>([&](ECS::Entity*, ECS::ComponentHandle<Render::TextComponent>comp)
			{
				matrix->data.MVPMatrix = DirectX::XMMatrixTranspose(
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
	: WinIntEventHandler()
	, _gfx(gfx)
	, _cursor(0,0)
{
	auto* vs = new Render::VertexShader(gfx, L"d3d11\\canvas_vs.cso", vertex2D_layout, ARRAYSIZE(UI::vertex2D_layout));
	gfx->shader_collection.insert(L"d3d11\\canvas_vs.cso", vs);

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
	const Position2 new_pos = { (float)mx,(float)-my };
	const MoveEvent move_event{new_pos - _cursor,new_pos};
	
	_cursor = new_pos;
	
	_gfx->main_scene->world()->each<InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<InteractiveForm> form)
		{
			form->on_mouse_move(move_event);
		});
}

void UI::UIContext::on_db_click()
{
	_gfx->main_scene->world()->each<InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<InteractiveForm> form)
		{
			form->on_db_click();
		});
}
