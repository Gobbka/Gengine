#pragma once
#include <DirectXMath.h>
#include <d3d11.h>

#define RGB_TO_FLOAT(r,g,b) r/255.f, g/255.f, b/255.f

struct __declspec(dllexport) Color3
{
	float r; float g; float b;
	Color3(float r, float g, float b) : r(r), g(g), b(b) {};
	Color3(float r, float g, float b, float a) : r(r), g(g), b(b) {};
	Color3(DirectX::XMFLOAT3 f3) : r(f3.x), g(f3.y), b(f3.z) {};

	DirectX::XMFLOAT3 to_float3();
};

struct __declspec(dllexport) Color4 : Color3
{
	float a = 1.f;
	Color4(float r, float g, float b, float a) : Color3(r, g, b), a(a) {};
	Color4(float r, float g, float b) : Color3(r, g, b) {};
	Color4(Color3 c) : Color3(c) {}

	DirectX::XMFLOAT4 to_float4() const;
};

struct __declspec(dllexport) Surface {
	float width;
	float height;

	Surface(float w, float h);
	Surface(RECT rect);
};

struct __declspec(dllexport) Vector2 {
	float x;
	float y;

	void operator +=(Vector2 pos);
	void operator -=(Vector2 pos);
	
	Vector2(float x, float y);
};

struct __declspec(dllexport) Vector3 : public Vector2 {
	float z;

	void operator +=(Vector3 pos);
	void operator -=(Vector3 pos);

	Vector3(float x, float y, float z);

	static Vector3 null();
};

typedef __declspec(dllexport) Vector2 Position2;
typedef __declspec(dllexport) Vector3 Position3;


