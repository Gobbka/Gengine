#pragma once

#define RGB_TO_FLOAT(r,g,b) (r)/255.f, (g)/255.f, (b)/255.f

template<typename T>
struct __declspec(dllexport) Color3 {
	T r, g, b;
};

template<typename T>
struct __declspec(dllexport) Color4 {
	T r, g, b, a;
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
	static Color3XM from_rgb(float r, float g, float b) { return Color3XM(RGB_TO_FLOAT(r,g,b)); }

	DirectX::XMFLOAT3 to_float3();
};

struct __declspec(dllexport) Color4XM : Color3XM
{
	float a = 1.f;
	Color4XM(float r, float g, float b, float a) : Color3XM(r, g, b), a(a) {}
	Color4XM(float r, float g, float b) : Color3XM(r, g, b) {}
	Color4XM(Color3XM c) : Color3XM(c) {}

	DirectX::XMFLOAT4 to_float4() const;
};
