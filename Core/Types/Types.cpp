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

void Vector2::operator+=(Vector2 pos)
{
	x += pos.x;
	y += pos.y;
}

void Vector2::operator-=(Vector2 pos)
{
	x -= pos.x;
	y -= pos.y;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Vector3::operator+=(Vector3 pos)
{
	this->z += pos.z;
	Position2::operator+=((Vector2)pos);
}

void Vector3::operator-=(Vector3 pos)
{
	this->z -= pos.z;
	Vector2::operator-=((Vector2)pos);
}

Vector3::Vector3(float x, float y, float z)
	: Vector2(x,y)
{
	this->z = z;
}

Vector3 Vector3::null()
{
	return Vector3(0, 0, 0);
}

Vector4::Vector4(float x, float y, float z, float w)
	: Vector3(x,y,z),
	w(w)
{

}

float Vector4::length()
{
	return DirectX::XMVector4Length(DirectX::XMVectorSet(x, y, z, w)).m128_f32[0];
}

Vector4 Vector4::normalize()
{
	auto vector =DirectX::XMVector4Normalize(DirectX::XMVectorSet(x, y, z, w));
	return Vector4(vector.m128_f32[0], vector.m128_f32[1], vector.m128_f32[2], vector.m128_f32[3]);
}

Vector4 Vector4::null()
{
	return Vector4(0, 0, 0, 0);
}

Vector4Int::Vector4Int(int x, int y, int z, int w)
	: x(x),y(y),z(z),w(w)
{

}
