#include "DirectionLightComponent.h"

#include "../../Graphics.h"
#include "../../IGContext.h"
#include "../Engine/MaskEngine.h"

Render::DirectionLightComponent::DirectionLightComponent(Core::GraphicsContext* gcontext)
	: WorldViewer(gcontext->get_screen_resolution())
	, context(gcontext)
	, mask_engine(new MaskEngine(context,context->get_screen_resolution(),MaskEngineUsage::Depth))
{
	WorldViewer::adjust_position(Position3(-2, -2, -2));
}

Render::DirectionLightComponent::DirectionLightComponent(DirectionLightComponent&&other) noexcept
	: WorldViewer(other)
	, context(other.context)
	, mask_engine(other.mask_engine)
{
	other.mask_engine = nullptr;
}

Render::DirectionLightComponent& Render::DirectionLightComponent::operator=(DirectionLightComponent&& other) noexcept
{
	*(WorldViewer*)this = std::move((WorldViewer&)other);
	mask_engine = other.mask_engine;

	other.mask_engine = nullptr;

	return*this;
}

void Render::DirectionLightComponent::bind() const
{
	context->get_context()->set_mask_engine(mask_engine);
	context->dss_collection[(DSBitSet)DepthStencilUsage::depth].bind(0);
}
