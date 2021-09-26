#include "WorldViewer.h"

#include "../../Graphics.h"
#include "../Engine/MaskEngine.h"
#include "../Engine/RenderTarget.h"

void Render::WorldViewer::update_position()
{
	_viewMatrix = create_view_matrix();
}

void Render::WorldViewer::update_rotation()
{
	_viewMatrix = create_view_matrix();
}

DirectX::XMMATRIX Render::WorldViewer::create_view_matrix()
{
	auto rotation = _transform.get_rotation();

	auto pos = _transform.get_position();
	auto xm_cam_pos = DirectX::XMVectorSet(pos.z, pos.y, pos.x, 0.f);
	auto camRotMatrix = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	auto camTarget = DirectX::XMVector3TransformCoord(Core::Transform::forward(), camRotMatrix);

	camTarget = DirectX::XMVectorAdd(camTarget, xm_cam_pos);

	auto upDir = DirectX::XMVector3TransformCoord(Core::Transform::up(), camRotMatrix);

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
		proj_matrix = DirectX::XMMatrixOrthographicLH(resolution.width, resolution.height, 0.0, farz);
	break;
	case WVProjectionType::Perspective:
		proj_matrix = DirectX::XMMatrixPerspectiveFovLH(
			(fov / 360.f) * DirectX::XM_2PI,
			resolution.width / resolution.height,
			0.1f,
			farz
		);
	break;
	}

	return scale == 1.f ? proj_matrix : proj_matrix * DirectX::XMMatrixScaling(
		scale, scale, 1.f
	);
}

Render::WorldViewer::WorldViewer(Core::GraphicsContext* context, RenderTarget* target)
	: _transform({0,0,0}),
	_resolution(0,0)
{
	this->context = context;

	if(target != nullptr)
	{
		_resolution = Surface(target->get_texture()->width(), target->get_texture()->height());
		render_target = target;
	}else
	{
		_resolution = context->get_screen_resolution();
	}

	update_position();
	
	_projectionMatrix = create_projection_matrix(projection,_resolution, _fov, _far_z, _scale);
}

void Render::WorldViewer::set_scale(float scale)
{
	_scale = scale;
	_projectionMatrix = create_projection_matrix(projection,_resolution,_fov,_scale);
}

void Render::WorldViewer::set_fov(float fov)
{
	_fov = fov;
	_projectionMatrix = create_projection_matrix(projection,_resolution, _fov, _far_z, _scale);
}

void Render::WorldViewer::set_farz(float farz)
{
	_far_z = farz;
	_projectionMatrix = create_projection_matrix(projection,_resolution, _fov, _far_z, _scale);
}

Render::MaskEngine* Render::WorldViewer::get_mask_engine()
{
	return mask_engine;
}

Core::GraphicsContext* Render::WorldViewer::graphics_context()
{
	return context;
}

Render::RenderTarget* Render::WorldViewer::get_render_target()
{
	return render_target;
}

Surface Render::WorldViewer::get_view_resolution()
{
	return _resolution;
}

void Render::WorldViewer::set_view_resolution(Surface surface)
{
	_resolution = surface;
	_projectionMatrix = create_projection_matrix(projection,_resolution, _fov, _far_z, _scale);
}

Vector3 Render::WorldViewer::point_to_world(Vector2 screen_coordinate)
{
	// TODO: handle that depth stencil texture2d can have D24_S8 format or D32 format

	BYTE depth;
	ID3D11Resource* view_resource;
	D3D11_TEXTURE2D_DESC texture_desc;

	mask_engine->get_view()->GetResource(&view_resource);
	((ID3D11Texture2D*)view_resource)->GetDesc(&texture_desc);
	
	

	D3D11_MAPPED_SUBRESOURCE map;

	context->context->Map(view_resource, 0, D3D11_MAP_READ, 0, &map);
	depth = ((BYTE*)map.pData)[(UINT)screen_coordinate.x * texture_desc.Width + (UINT)screen_coordinate.y];
	context->context->Unmap(view_resource, 0);

	if (texture_desc.Format == DXGI_FORMAT_D24_UNORM_S8_UINT)
		depth = depth >> 8;

	return Vector3(screen_coordinate.x, screen_coordinate.y, depth * _far_z);
}

DirectX::XMMATRIX Render::WorldViewer::world_to_screen_matrix()
{
	return _viewMatrix * _projectionMatrix;
}

void Render::WorldViewer::bind()
{
	auto* mask_view = mask_engine != nullptr ? mask_engine->get_view() : nullptr;
	
	render_target->bind(mask_view);
	
}
