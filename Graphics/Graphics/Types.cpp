#include "Types.h"

DirectX::XMFLOAT3 Color3::to_float3()
{
	return DirectX::XMFLOAT3(r, g, b);
}

DirectX::XMFLOAT4 Color4::to_float4() const
{
	return DirectX::XMFLOAT4( r,g,b,a );
}

Surface::Surface(float w, float h)
{
	width = w;
	height = h;
}

Surface::Surface(RECT rect)
{
	width = (float)(rect.right - rect.left);
	height = (float)(rect.bottom - rect.top);
}

void Position2::operator+=(Position2 pos)
{
	x += pos.x;
	y += pos.y;
}

Position2::Position2(float x, float y)
{
	this->x = x;
	this->y = y;
}
