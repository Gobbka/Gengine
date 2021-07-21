#include "Transform.h"


Core::Transform::Transform(Position3 pos)
	: _pos(pos)
{
	
}

void Core::Transform::adjust_position(Position3 pos)
{
	_pos += pos;
}

void Core::Transform::set_position(Position3 pos)
{
	_pos = pos;
}

Position3 Core::Transform::get_position()
{
	return _pos;
}

Core::Quaternion3::Quaternion3(Vector3 rotation)
	: _rotation(rotation)
{
}

void Core::Quaternion3::adjust_rotation(Vector3 rot)
{
	_rotation += rot;
}

Vector3 Core::Quaternion3::get_rotation()
{
	return _rotation;
}
