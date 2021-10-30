#pragma once
#include <Types/Types.h>

struct __declspec(dllexport) PointLightComponent {
	float     intensity;
	Color3XM  color;
	Position3 position;
};
