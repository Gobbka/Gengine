#include "DirectionLight.h"


#include "../../Graphics.h"
#include "../Engine/MaskEngine.h"
#include "../Engine/RenderTarget.h"

Render::DirectionLight::DirectionLight(Core::GraphicsContext* gcontext)
	: WorldViewer(gcontext,new RenderTarget(gcontext, gcontext->get_screen_resolution()))
{
	_mask_engine = new MaskEngine(this,MaskEngineUsage::Depth);
	_transform.adjust_position(Position3(0, -5, 0));
	update_position();
}

void Render::DirectionLight::create_shadowmap()
{
	graphics_context()->get_sprite_engine()->set_ps_state(false);

	
	context->begin_3d();

	matrix_buffer.bind();
	
	_mask_engine->clear_buffer();
	render_target->bind(_mask_engine->get_view());

	_mask_engine->set_state(_mask_engine->get_disabledState(), 0, true);
	_mask_engine->bind();
	
	auto objects = context->worldspace()->objects;

	for (auto* object : objects)
	{
		this->view(object);
	}

	graphics_context()->get_sprite_engine()->set_ps_state(true);
}
