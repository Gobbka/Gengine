#include "WorldViewer.h"

#include "../Engine/RenderTarget.h"
#include "../Events/RenderEvent.h"
#include "../Model/Model.h"

const static DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_BACKWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_LEFT_VECTOR = DirectX::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_RIGHT_VECTOR = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

void Render::WorldViewer::update_position()
{
	auto camPos = _transform.get_position();
	_xm_camPosition = DirectX::XMVectorSet(camPos.z, camPos.y, camPos.x, 0.f);
	_viewMatrix = create_view_matrix();
}

void Render::WorldViewer::update_rotation()
{
	_viewMatrix = create_view_matrix();
}

DirectX::XMMATRIX Render::WorldViewer::create_view_matrix()
{
	auto rotation = _transform.get_rotation();

	auto camRotMatrix = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	auto camTarget = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, camRotMatrix);

	camTarget = DirectX::XMVectorAdd(camTarget, _xm_camPosition);

	auto upDir = DirectX::XMVector3TransformCoord(DEFAULT_UP_VECTOR, camRotMatrix);

	return DirectX::XMMatrixLookAtLH(
		_xm_camPosition,
		camTarget,
		upDir
	);
}

DirectX::XMMATRIX Render::WorldViewer::create_projection_matrix(Surface resolution, float fov, float scale)
{
	auto forRadians = (fov / 360.f) * DirectX::XM_2PI;

	auto res = resolution;
	auto aspectRatio = res.width / res.height;

	return DirectX::XMMatrixPerspectiveFovLH(forRadians, aspectRatio, 0.1f, 120.f) * DirectX::XMMatrixScaling(scale, scale, 1.f);
}

Render::WorldViewer::WorldViewer(Core::GraphicsContext* context, RenderTarget* target)
	: _transform({-4,0,0}),
	matrix_buffer(context,&_matrix_buffer_struct,sizeof(_matrix_buffer_struct)),
	_resolution(target->get_texture()->width(), target->get_texture()->height())
{
	this->context = context;
	render_target = target;
	
	_viewMatrix = create_view_matrix();
	_projectionMatrix = create_projection_matrix(_resolution,_fov,_scale);
}

void Render::WorldViewer::view(Model* model)
{
	auto modelMatrix = model->transform.get_world_matrix();
	_matrix_buffer_struct = { DirectX::XMMatrixTranspose(
		modelMatrix * _viewMatrix * _projectionMatrix
	) };
	matrix_buffer.update();
	
	model->draw(DrawEvent3D(context));
}

void Render::WorldViewer::set_scale(float scale)
{
	_scale = scale;
	_projectionMatrix = create_projection_matrix(_resolution,_fov,_scale);
}

void Render::WorldViewer::set_fov(float fov)
{
	_fov = fov;
	_projectionMatrix = create_projection_matrix(_resolution, _fov, _scale);
}

Core::GraphicsContext* Render::WorldViewer::graphics_context()
{
	return context;
}

Surface Render::WorldViewer::get_view_resolution()
{
	return _resolution;
}
