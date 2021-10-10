#include "DirectionLightComponent.h"

#include "../../Graphics.h"
#include "../../IGContext.h"
#include "../Engine/MaskEngine.h"

Render::DirectionLightComponent::DirectionLightComponent(Core::GraphicsContext* gcontext)
{
	context = gcontext;
	auto scr_res = context->get_screen_resolution();
	mask_engine = new MaskEngine(context, scr_res,MaskEngineUsage::Depth);

	WorldViewer::adjust_position(Position3(-2, -2, -2));
}

Render::DirectionLightComponent::DirectionLightComponent(DirectionLightComponent&&other) noexcept
	: WorldViewer(other)
{
	context = other.context;
	mask_engine = other.mask_engine;

	other.mask_engine = nullptr;
}

Render::DirectionLightComponent& Render::DirectionLightComponent::operator=(DirectionLightComponent&& other) noexcept
{
	*(WorldViewer*)this = std::move((WorldViewer&)other);

	return*this;
}

void Render::DirectionLightComponent::bind() const
{
	context->get_context()->set_mask_engine(mask_engine);
	mask_engine->get_disabledState()->bind();
}
