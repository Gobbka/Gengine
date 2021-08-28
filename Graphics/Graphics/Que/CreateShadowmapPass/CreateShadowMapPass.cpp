#include "CreateShadowMapPass.h"

#include "../../../Graphics.h"
#include "../../../IGContext.h"
#include "../../../Render/Engine/MaskEngine.h"
#include "../../../Render/Light/DirectionLightComponent.h"

void Render::CreateShadowMapPass::execute(Core::GraphicsContext* context)
{
	context->active_scene->world()->each<DirectionLightComponent>([&](ECS::Entity* ent, ECS::ComponentHandle<DirectionLightComponent> handle)
		{
			auto* gcontext = context->get_context();
			auto* old_ps = gcontext->get_pixel_shader();

			handle->bind();
			handle->get_mask_engine()->clear_buffer();
		
			gcontext->set_pixel_shader(nullptr);
			// do stuff here

			// clean up
			gcontext->set_pixel_shader(old_ps);
		});
}
