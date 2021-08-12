#include "DirectionLight.h"

Render::DirectionLight::DirectionLight(Core::GraphicsContext* context)
	: transform(Position3::null())
{
	_context = context;
}
