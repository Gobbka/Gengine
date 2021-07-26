#pragma once
#include <vector>

#include "RigidBody.h"

class __declspec(dllexport) PhysicsModule
{
	std::vector<RigidBody> _physics_elements;
public:
	void add_element(RigidBody element);

	void tick();
};
