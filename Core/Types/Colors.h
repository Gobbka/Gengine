#pragma once
#include <DirectXMath.h>
#define RGB_TO_FLOAT(r,g,b) (r)/255.f, (g)/255.f, (b)/255.f

template<typename T>
struct __declspec(dllexport) Color3 {
	T r, g, b;

	Color3(T r=0, T g=0, T b=0)
		: r(r), g(g), b(b)
	{}
};

template<typename T>
struct __declspec(dllexport) Color4 {
	T r, g, b, a;

	Color4(T r=0,T g=0,T b=0,T a=0)
		: r(r),g(g),b(b),a(a)
	{}
};

typedef Color3<unsigned char> Color3Byte;
typedef Color4<unsigned char> Color4Byte;

struct __declspec(dllexport) Color3XM
{
	float r; float g; float b;
	Color3XM(float r, float g, float b) : r(r), g(g), b(b) {}
	Color3XM(float r, float g, float b, float a) : r(r), g(g), b(b) {}
	Color3XM(DirectX::XMFLOAT3 f3) : r(f3.x), g(f3.y), b(f3.z) {}

	const static Color3XM black() { return Color3XM(0, 0, 0); }
	const static Color3XM white() { return { 1,1,1 }; }
	static Color3XM from_rgb(float r, float g, float b) { return Color3XM(RGB_TO_FLOAT(r,g,b)); }

	DirectX::XMFLOAT3 to_float3() const;

	Color3XM inverse() const
	{
		return { 1.f - r, 1.f - g, 1.f - b };
	}
};

struct __declspec(dllexport) Color4XM : Color3XM
{
	float a = 1.f;
	Color4XM(float r, float g, float b, float a) : Color3XM(r, g, b), a(a) {}
	Color4XM(float r, float g, float b) : Color3XM(r, g, b) {}
	Color4XM(Color3XM c) : Color3XM(c) {}

	DirectX::XMFLOAT4 to_float4() const;
};
