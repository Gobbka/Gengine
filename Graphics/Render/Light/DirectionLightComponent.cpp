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
	_transform.adjust_position(Position3(-2, -2, -2));

	update_position();
}

void Render::DirectionLightComponent::set_position(Position3 pos)
{
	_transform.set_position(pos);
	update_position();
}

void Render::DirectionLightComponent::set_rotation(Vector3 rot)
{
	_transform.set_rotation(rot);
	update_position();
}

void Render::DirectionLightComponent::bind()
{
	context->get_context()->set_mask_engine(mask_engine);
	mask_engine->get_disabledState()->bind();
}
