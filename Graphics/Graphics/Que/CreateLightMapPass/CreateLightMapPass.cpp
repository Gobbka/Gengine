#include "CreateLightMapPass.h"
#include "../../../Render/I3DObject/Cube/Cube.h"

void Render::CreateLightMapPass::execute()
{

}

Render::CreateLightMapPass::CreateLightMapPass(Core::GraphicsContext* context)
	: _point_light_cube(Cube::make_independent(context,Position3::null(),1))
{
	_context = context;
}
