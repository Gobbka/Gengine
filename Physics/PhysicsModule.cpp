#include "PhysicsModule.h"

void PhysicsModule::add_element(RigidBody element)
{
	_physics_elements.push_back(element);
}

void PhysicsModule::tick()
{
	for(auto element:_physics_elements)
	{
		element.target->adjust_position(element.force);
	}
}
