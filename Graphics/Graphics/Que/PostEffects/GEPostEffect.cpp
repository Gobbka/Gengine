#include "GEPostEffect.h"

#include "../../../Render/dx11_impl/Graphics.h"
#include "../../Geometric/2D.h"

void Render::GEPostEffect::do_effect()
{
	gfx->commander->draw_mesh(_screen_mesh);
}

Render::GEPostEffect::GEPostEffect(GEGraphics* context)
	: _screen_mesh(Geometric_2D::make_rectangle(context, { -1,1 }, { 2, 2 }))
	, gfx(context)
{
}
