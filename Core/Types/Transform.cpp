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
