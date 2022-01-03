#include "WorldViewer.h"

DirectX::XMMATRIX Render::WorldViewer::create_view_matrix()
{
	auto rotation = _transform.get_rotation();

	auto pos = _transform.get_position();
	auto xm_cam_pos = DirectX::XMVectorSet(pos.z, pos.y, pos.x, 0.f);
	auto camRotMatrix = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	auto camTarget = DirectX::XMVector3TransformCoord(Core::Transform::forward(), camRotMatrix);

	camTarget = DirectX::XMVectorAdd(camTarget, xm_cam_pos);

	const auto upDir = DirectX::XMVector3TransformCoord(Core::Transform::up(), camRotMatrix);

	return DirectX::XMMatrixLookAtLH(
		xm_cam_pos,
		camTarget,
		upDir
	);
}

DirectX::XMMATRIX Render::WorldViewer::create_projection_matrix(WVProjectionType projection, Surface resolution, float fov, float farz, float scale)
{
	DirectX::XMMATRIX proj_matrix;

	switch (projection)
	{
	case WVProjectionType::Orthographic:
		proj_matrix = DirectX::XMMatrixOrthographicLH(1, 1, 0.0, farz);
	break;
	case WVProjectionType::Perspective:
		proj_matrix = DirectX::XMMatrixPerspectiveFovLH(
			(fov / 360.f) * DirectX::XM_2PI,
			resolution.width / resolution.height,
			0.1f,
			farz
		);
	break;
	default:
		proj_matrix = DirectX::XMMatrixIdentity();
	break;
	}

	return scale == 1.f ? proj_matrix : proj_matrix * DirectX::XMMatrixScaling(
		scale, scale, 1.f
	);
}

DirectX::XMMATRIX Render::WorldViewer::create_projection_matrix() const
{
	return create_projection_matrix(projection, _resolution, _fov, _far_z, _scale);
}

Render::WorldViewer::WorldViewer(Surface resolution)
	: _transform({0,0,0})
	, _resolution(resolution)
	, _projectionMatrix(create_projection_matrix())
	, _viewMatrix(create_view_matrix())
{
}

Render::WorldViewer::WorldViewer(WorldViewer& other)
	:
	_transform(other._transform),
	projection(other.projection),
	_resolution(other._resolution),
	_projectionMatrix(other._projectionMatrix),
	_viewMatrix(other._viewMatrix)
{
}

void Render::WorldViewer::set_projection_type(WVProjectionType type)
{
	projection = type;
	_projectionMatrix = create_projection_matrix();
}

void Render::WorldViewer::set_scale(const float scale)
{
	_scale = scale;
	_projectionMatrix = create_projection_matrix();
}

void Render::WorldViewer::set_fov(const float fov)
{
	_fov = fov;
	_projectionMatrix = create_projection_matrix();
}

void Render::WorldViewer::set_farz(const float farz)
{
	_far_z = farz;
	_projectionMatrix = create_projection_matrix();
}

Surface Render::WorldViewer::get_view_resolution() const
{
	return _resolution;
}

void Render::WorldViewer::set_view_resolution(Surface surface)
{
	_resolution = surface;
	_projectionMatrix = create_projection_matrix(projection,_resolution, _fov, _far_z, _scale);
}

DirectX::XMMATRIX Render::WorldViewer::world_to_screen_matrix() const
{
	return _viewMatrix * _projectionMatrix;
}

DirectX::XMMATRIX Render::WorldViewer::view_matrix() const
{
	return _viewMatrix;
}

DirectX::XMMATRIX Render::WorldViewer::projection_matrix() const
{
	return _projectionMatrix;
}

DirectX::XMMATRIX Render::WorldViewer::rotation_matrix() const
{
	const auto rotation = _transform.get_rotation();

	const auto xm_cam_pos = DirectX::XMVectorSet(0, 0, 0, 0.f);
	const auto camRotMatrix = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	auto camTarget = DirectX::XMVector3TransformCoord(Core::Transform::forward(), camRotMatrix);

	camTarget = DirectX::XMVectorAdd(camTarget, xm_cam_pos);

	const auto upDir = DirectX::XMVector3TransformCoord(Core::Transform::up(), camRotMatrix);

	return DirectX::XMMatrixLookAtLH(
		xm_cam_pos,
		camTarget,
		upDir
	);
}

void Render::WorldViewer::set_position(const Position3 pos)
{
	_transform.set_position(pos);
	_viewMatrix = create_view_matrix();
}

void Render::WorldViewer::adjust_position(const Position3 pos)
{
	_transform.adjust_position(pos);
	_viewMatrix = create_view_matrix();
}

void Render::WorldViewer::adjust_position_relative(const Position3 pos)
{
	_transform.adjust_position(pos);
	_viewMatrix = create_view_matrix();
}

void Render::WorldViewer::set_rotation(const Vector3 rot)
{
	_transform.set_rotation(rot);
	_viewMatrix = create_view_matrix();
}

void Render::WorldViewer::adjust_rotation(const Vector3 rot)
{
	_transform.adjust_rotation(rot);
	_viewMatrix = create_view_matrix();
}

