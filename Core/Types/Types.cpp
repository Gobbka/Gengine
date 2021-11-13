#include "Types.h"

DirectX::XMFLOAT3 Color3XM::to_float3() const
{
	return DirectX::XMFLOAT3(r, g, b);
}

DirectX::XMFLOAT4 Color4XM::to_float4() const
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

bool Vector2::operator==(Vector2 vector) const
{
	return x == vector.x && y == vector.y;
}

Vector2 Vector2::lerp(Vector2 vector,float t) const
{
	auto T = DirectX::XMVectorSet(x, y, 0, 0);
	auto O = DirectX::XMVectorSet(vector.x, vector.y, 0, 0);
	auto result = DirectX::XMVectorLerp(T, O, t);
	return { result.m128_f32[0], result.m128_f32[1] };
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2 Vector2::operator+(Vector2& first) const
{
	return { x + first.x,y + first.y };
}

Vector2 Vector2::operator-(Vector2& other) const
{
	return { x - other.x,y - other.y };
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
	: Vector2(x,y),
	z(z)
{}

inline Vector3 Vector3::null()
{
	return { 0, 0, 0};
}

Vector4::Vector4(float x, float y, float z, float w)
	: Vector3(x,y,z),
	w(w)
{}

float Vector4::length() const
{
	return DirectX::XMVector4Length(DirectX::XMVectorSet(x, y, z, w)).m128_f32[0];
}

Vector4 Vector4::normalize() const
{
	auto vector = DirectX::XMVector4Normalize(DirectX::XMVectorSet(x, y, z, w));
	return { vector.m128_f32[0], vector.m128_f32[1], vector.m128_f32[2], vector.m128_f32[3] };
}

inline Vector4 Vector4::null()
{
	return { 0, 0, 0, 0 };
}

Vector4Int::Vector4Int(int x, int y, int z, int w)
	: x(x),y(y),z(z),w(w)
{

}
