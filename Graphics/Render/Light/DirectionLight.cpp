#include "DirectionLight.h"


#include "../../Graphics.h"
#include "../Engine/MaskEngine.h"
#include "../Engine/RenderTarget.h"

Render::DirectionLight::DirectionLight(Core::GraphicsContext* gcontext)
	: WorldViewer(gcontext,gcontext->get_shadow_render_target())
{
	auto scr_res = gcontext->get_screen_resolution();
	_mask_engine = new MaskEngine(this,MaskEngineUsage::Depth,&scr_res);
	_transform.adjust_position(Position3(0, -5, 0));
	update_position();
}

void Render::DirectionLight::create_shadowmap()
{
	graphics_context()->get_sprite_engine()->set_ps_state(false);
	
	context->begin_3d();

	matrix_buffer.bind();
	
	_mask_engine->clear_buffer();
	render_target->clear(Color3::black());
	render_target->bind(_mask_engine->get_view());

	_mask_engine->get_disabledState()->bind();

	auto objects = context->worldspace()->objects;

	for (auto* object : objects)
	{
		this->view(object);
	}

	graphics_context()->get_sprite_engine()->set_ps_state(true);
}
