#include "UIContext.h"

#include <Graphics.h>
#include <Render/Common/IGContext.h>
#include <Graphics/Camera.h>
#include <Render/d3d/Buffer/ConstantBuffer.h>
#include <Render/d3d/Shader/VertexShader.h>
#include "InteractiveForm.h"
#include "Canvas/Vertex2D.h"

class DrawUIPass : public Render::IPass
{
	Render::GEGraphics* _context;
	Render::ConstantBuffer<Render::MVPStruct> _mvp_struct;
public:
	void execute(Render::Scene*scene) override
	{
		auto* gcontext = _context->get_context();
		gcontext->debug_message("DrawUIPass executed");

		auto* camera = scene->get_main_camera()->get<Render::Camera>().get_ptr();
		camera->bind();
		auto resolution = camera->get_view_resolution();

		gcontext->set_topology(PrimitiveTopology::TRIANGLELIST);
		_mvp_struct.data.MVPMatrix = XMMatrixTranspose(
			DirectX::XMMatrixOrthographicLH(resolution.width,resolution.height,0.0,1.f) * DirectX::XMMatrixTranslation(-1,1,0)
		);
		_mvp_struct.update();
		_mvp_struct.bind();

		const auto* mask_engine = camera->get_mask_engine();

		_context->dss_collection[(Render::DSBitSet)Render::DepthStencilUsage::stencil_mask].bind(0);

		auto* old_ps = gcontext->get_pixel_shader();
		auto* old_vs = gcontext->get_vertex_shader();

		gcontext->set_pixel_shader(_context->shader_collection.get<Render::PixelShader>(L"d3d11\\canvas_ps.cso"));
		gcontext->set_vertex_shader(_context->shader_collection.get_vs(L"d3d11\\canvas_vs.cso"));

		scene->world()->each<UI::InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<UI::InteractiveForm>form)
			{
				if (form->hidden())
					return;

				form->render();
			});

		gcontext->set_pixel_shader(old_ps);
		gcontext->set_vertex_shader(old_vs);

		mask_engine->clear_buffer();
	}

	DrawUIPass(Render::GEGraphics*context)
		: _context(context)
		, _mvp_struct(context,0)
	{}
};

ECS::Entity* UI::UIContext::create_layer()
{
	auto* ent = _gfx->main_scene->world()->create();
	auto handle = ent->assign<InteractiveForm>(_gfx, &_cursor);
	handle->show();
	return ent;
}

UI::UIContext::UIContext(Render::GEGraphics* gfx,Render::Scene* scene)
	: WinIntEventHandler()
	, _gfx(gfx)
	, _cursor(0,0)
{
	auto* vs = new Render::VertexShader(gfx, L"d3d11\\canvas_vs.cso", vertex2D_layout, ARRAYSIZE(UI::vertex2D_layout));
	gfx->shader_collection.insert(L"d3d11\\canvas_vs.cso", vs);

	scene->render_pipeline().add_pass(new DrawUIPass(gfx), Render::PassStep::overlay);
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
