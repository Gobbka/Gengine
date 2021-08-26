#include "D11GContext.h"

Render::D11GContext::D11GContext(Core::GraphicsContext* context, ID3D11DeviceContext* d11context)
	: IGContext(context)
{
	_d11context = d11context;
}

void Render::D11GContext::set_topology(PrimitiveTopology topology)
{
	switch (topology)
	{
	case PrimitiveTopology::TRIANGLELIST:
		_d11context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case PrimitiveTopology::TRIANGLESTRIP:
		_d11context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		break;
	}
}
