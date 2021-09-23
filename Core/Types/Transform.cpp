#include "Transform.h"

#include <iostream>

DirectX::XMVECTOR DEFAULT_BACKWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
DirectX::XMVECTOR DEFAULT_LEFT_VECTOR = DirectX::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);

DirectX::XMMATRIX Core::Transform::create_world_matrix()
{
	return DirectX::XMMatrixRotationRollPitchYaw(_rotation.x,_rotation.y,_rotation.z) * DirectX::XMMatrixTranslation(_pos.x, _pos.y, _pos.z);
}

DirectX::XMMATRIX Core::Transform::get_world_matrix() const
{
	return _world_matrix;
}

Core::Transform::Transform(Position3 pos)
	: _pos(pos),
	_rotation(0, 0, 0),
	_world_matrix(create_world_matrix()),
	_forward_vector(Transform::forward()),
	_up_vector(Transform::up()),
	_right_vector(Transform::right())
{
}

void Core::Transform::adjust_position(Position3 pos)
{
	using namespace DirectX;
	auto nigga = (_forward_vector * pos.x) + (_right_vector * pos.z) + (_up_vector * pos.y);

	XMFLOAT3 forw;
	XMStoreFloat3(&forw, nigga);
	
	_pos += Position3(forw.z,forw.y,forw.x);
	_world_matrix = create_world_matrix();
}

void Core::Transform::set_position(Position3 pos)
{
	_pos = pos;
	
	_world_matrix = create_world_matrix();
}

void Core::Transform::adjust_rotation(Vector3 rotation)
{
	_rotation += rotation;

	auto rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, 0);
	_forward_vector = DirectX::XMVector3TransformCoord(Transform::forward(), rotationMatrix);
	_right_vector = DirectX::XMVector3TransformCoord(Transform::right(), rotationMatrix);
	_up_vector = DirectX::XMVector3TransformCoord(Transform::up(), rotationMatrix);
	
	_world_matrix = create_world_matrix();
}

void Core::Transform::set_rotation(Vector3 rotation)
{
	_rotation = rotation;
	_world_matrix = create_world_matrix();
}

Position3 Core::Transform::get_position_lh()
{
	return Position3(_pos.z, _pos.y, _pos.x);
}

Position3 Core::Transform::get_position()
{
	return _pos;
}

Vector3 Core::Transform::get_rotation()
{
	return _rotation;
}

DirectX::XMVECTOR Core::Transform::up()
{
	return DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
}

DirectX::XMVECTOR Core::Transform::right()
{
	return DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
}

DirectX::XMVECTOR Core::Transform::forward()
{
	return DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
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
