#include "DirectionLightComponent.h"


#include "../../Graphics.h"
#include "../../IGContext.h"
#include "../Engine/MaskEngine.h"
#include "../Engine/RenderTarget.h"

Render::DirectionLightComponent::DirectionLightComponent(Core::GraphicsContext* gcontext)
	: WorldViewer(gcontext,nullptr)
{
	auto scr_res = gcontext->get_screen_resolution();
	mask_engine = new MaskEngine(this,MaskEngineUsage::Depth,&scr_res);
	_transform.adjust_position(Position3(0, -5, 0));
	update_position();
}

void Render::DirectionLightComponent::bind()
{
	mask_engine->clear_buffer();
	context->get_context()->set_mask_engine(mask_engine);
	mask_engine->get_disabledState()->bind();
	
}