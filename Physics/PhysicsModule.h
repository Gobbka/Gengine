#pragma once
#include <vector>
#include <Ecs/Ecs.h>

#include "RigidBody.h"

class __declspec(dllexport) PhysicsModule : public ECS::EntitySystem
{
public:
	float gravity_const = 10.f;
	float air_resistance_coefficient = 0.2f;
	
	void tick(ECS::World* world, ECS::DefaultTickData data) override;
};
