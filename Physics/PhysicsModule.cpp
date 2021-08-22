#include "PhysicsModule.h"

void PhysicsModule::tick(ECS::World* world, ECS::DefaultTickData data)
{
	world->each<RigidBody>([&](ECS::Entity* ent, ECS::ComponentHandle<RigidBody> body)
		{
			body->target->adjust_position(Position3(body->force.x * data, body->force.y * data, 0));

			body->force.y -= gravity_const * data;
			if(body->force.x > 0.5f)
			{
				body->force.x *= 1.f - air_resistance_coefficient;
			}else
			{
				body->force.x = 0;
			}
			
		});
}
