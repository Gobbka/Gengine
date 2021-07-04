#pragma once
#include <DirectXMath.h>

#define RGB_TO_FLOAT(r,g,b) r/255.f, g/255.f, b/255.f

struct Color3
{
	float r; float g; float b;
	Color3(float r, float g, float b) : r(r), g(g), b(b) {};
	Color3(float r, float g, float b, float a) : r(r), g(g), b(b) {};
	Color3(DirectX::XMFLOAT3 f3) : r(f3.x), g(f3.y), b(f3.z) {};
};

struct Color4 : Color3
{
	float a = 1.f;
	Color4(float r, float g, float b, float a) : Color3(r, g, b), a(a) {};
	Color4(float r, float g, float b) : Color3(r, g, b) {};
	Color4(Color3 c) : Color3(c) {}
};

struct Surface {
	float width;
	float height;

	Surface(float w, float h);
};

struct Position2 {
	float x;
	float y;

	Position2(float x, float y);
};


