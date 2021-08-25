#include "D11GContext.h"

Render::D11GContext::D11GContext(Core::GraphicsContext* context, ID3D11DeviceContext* d11context)
	: IGContext(context)
{
	_d11context = d11context;
}
