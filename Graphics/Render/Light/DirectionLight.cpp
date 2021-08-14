#include "DirectionLight.h"


#include "../../Graphics.h"
#include "../Engine/MaskEngine.h"
#include "../Engine/RenderTarget.h"

Render::DirectionLight::DirectionLight(Core::GraphicsContext* gcontext)
	: WorldViewer(gcontext,new RenderTarget(gcontext, gcontext->get_screen_resolution()))
{
	_mask_engine = new MaskEngine(this,MaskEngineUsage::Depth);
}

void Render::DirectionLight::create_shadowmap()
{
	context->begin_3d();

	matrix_buffer.bind();
	
	_mask_engine->clear_buffer();
	_mask_engine->set_state(_mask_engine->get_disabledState(), 0, true);
	_mask_engine->bind();
	
	context->context->PSSetShader(nullptr, nullptr, 0);
	
	auto objects = context->worldspace()->objects;

	for (auto* object : objects)
	{
		this->view(object);
	}
}
