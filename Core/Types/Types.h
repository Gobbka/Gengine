#pragma once
#include <d3d11.h>
#include "Colors.h"

struct __declspec(dllexport) Vector2 {
	float x;
	float y;

	void operator +=(Vector2 pos);
	void operator -=(Vector2 pos);
	Vector2 lerp(Vector2 vector,float t) const;

	Vector2(float x, float y);
};

struct __declspec(dllexport) Vector3 : public Vector2 {
	float z;

	void operator +=(Vector3 pos);
	void operator -=(Vector3 pos);

	Vector3(float x, float y, float z);

	static inline Vector3 null();
};

struct __declspec(dllexport) Vector4 : public Vector3 {
	float w;

	Vector4(float x, float y, float z, float w);

	float length() const;
	Vector4 normalize() const;

	static inline Vector4 null();
};

struct __declspec(dllexport) Vector4Int {
	int x, y, z, w;

	Vector4Int(int x,int y,int z,int w);
};

struct __declspec(dllexport) Vector2Int {
	int x, y;

	Vector2Int(int x, int y) : x(x),y(y) {}
};

struct __declspec(dllexport) Surface {
	float width;
	float height;

	Surface(float w, float h);
	Surface(RECT rect);

	Vector2Int to_vector2int() const
	{
		return {(int)width, (int)height};
	}
};

typedef __declspec(dllexport) Vector2 Position2;
typedef __declspec(dllexport) Vector3 Position3;


