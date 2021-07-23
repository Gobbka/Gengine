#include "Transform.h"


void Core::Transform::update_world_matrix()
{
	_world_matrix = DirectX::XMMatrixRotationRollPitchYaw(_rotation.x,_rotation.y,_rotation.z) * DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);
}

DirectX::XMMATRIX Core::Transform::get_world_matrix() const
{
	return _world_matrix;
}

Core::Transform::Transform(Position3 pos)
	: _pos(pos),
	_rotation(0,0,0)
{
	update_world_matrix();
}

void Core::Transform::adjust_position(Position3 pos)
{
	_pos += pos;
	update_world_matrix();
}

void Core::Transform::set_position(Position3 pos)
{
	_pos = pos;
	update_world_matrix();
}

void Core::Transform::adjust_rotation(Vector3 rotation)
{
	_rotation += rotation;
	update_world_matrix();
}

void Core::Transform::set_rotation(Vector3 rotation)
{
	_rotation = rotation;
	update_world_matrix();
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
