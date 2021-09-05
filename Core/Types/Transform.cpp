#include "Transform.h"

#include <iostream>

DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
DirectX::XMVECTOR DEFAULT_BACKWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
DirectX::XMVECTOR DEFAULT_LEFT_VECTOR = DirectX::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
DirectX::XMVECTOR DEFAULT_RIGHT_VECTOR = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

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
	_rotation(0,0,0),
	_forward_vector(DEFAULT_FORWARD_VECTOR),
	_up_vector(DEFAULT_UP_VECTOR),
	_right_vector(DEFAULT_RIGHT_VECTOR)
{
	update_world_matrix();
}

void Core::Transform::adjust_position(Position3 pos)
{
	using namespace DirectX;
	auto nigga = (_forward_vector * pos.x) + (_right_vector * pos.z) + (_up_vector * pos.y);

	XMFLOAT3 forw;
	XMStoreFloat3(&forw, nigga);
	
	_pos += Position3(forw.z,forw.y,forw.x);
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

	auto rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, 0);
	_forward_vector = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, rotationMatrix);
	_right_vector = DirectX::XMVector3TransformCoord(DEFAULT_RIGHT_VECTOR, rotationMatrix);
	_up_vector = DirectX::XMVector3TransformCoord(DEFAULT_UP_VECTOR, rotationMatrix);
	
	update_world_matrix();
}

void Core::Transform::set_rotation(Vector3 rotation)
{
	_rotation = rotation;
	update_world_matrix();
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
