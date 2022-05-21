#include "SmoothPostEffect.h"

Render::SmoothPostEffect::SmoothPostEffect(GEGraphics* gfx)
	: GEPostEffect(gfx)
{
}

void Render::SmoothPostEffect::execute(Scene* scene)
{

	do_effect();
}
