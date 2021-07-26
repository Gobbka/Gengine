#include "RigidBody.h"

RigidBody::RigidBody(Core::Transform* lp_target)
	: force(0,0,0)
{
	target = lp_target;
}
