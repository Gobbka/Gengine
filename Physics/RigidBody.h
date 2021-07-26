#pragma once
#include "Types/Transform.h"

struct __declspec(dllexport) RigidBody
{
	Core::Transform* target;

	Vector3 force;
	
	explicit RigidBody(Core::Transform*lp_target);
};
