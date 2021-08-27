#include "Camera.h"

#include "BlendEngine.h"
#include "MaskEngine.h"
#include "Types/Types.h"

#include <DirectXMath.h>
#include <iostream>

void Render::Camera::clear(Color3 color)
{
	render_target->clear(color);
}

void Render::Camera::clear()
{
	render_target->clear();
}

void Render::Camera::set_position(Position3 pos)
{
	_transform.set_position(pos);
	update_position();
}

void Render::Camera::adjust_position(Position3 pos)
{
	_transform.adjust_position(pos);
	update_position();
}

void Render::Camera::adjust_position_relative(Position3 pos)
{
	_transform.adjust_position(pos);
	update_position();
}

void Render::Camera::adjust_rotation(Vector3 rot)
{
	_transform.adjust_rotation(rot);
	update_rotation();
}

void Render::Camera::set_resolution(Surface resolution)
{
	////_resolution = resolution;
	//matrix2d_buffer->data = { DirectX::XMMatrixScaling(1.f / (resolution.width / 2),1.f / (resolution.height / 2),1.f) };
	////_projectionMatrix = create_proj_matrix();
	//
	//matrix2d_buffer->update();
}

void Render::Camera::set_render_target(RenderTarget* target)
{
	_cameraOptions.renderTarget = target;
}

Render::CameraOptions* Render::Camera::options()
{
	return &_cameraOptions;
}

Core::GraphicsContext* Render::Camera::graphics_context()
{
	return context;
}

ID3D11Device* Render::Camera::device() const
{
	return context->device;
}

Render::RenderTarget* Render::Camera::get_target_view() const
{
	return _cameraOptions.renderTarget;
}

Render::MaskEngine* Render::Camera::get_mask_engine() const
{
	return mask_engine;
}

Render::BlendEngine* Render::Camera::blend_engine() const
{
	return _blendEngine;
}

Surface Render::Camera::get_screen_resolution() const
{
	return context->get_screen_resolution();
}

Render::Camera::Camera(Core::GraphicsContext* context,RenderTarget*target)
	:
	WorldViewer(context,target)
{
	_cameraOptions.renderTarget = target;
	_blendEngine = new BlendEngine(context);
	
	auto _resolution = get_view_resolution();

	mask_engine = new MaskEngine(this);
}

void Render::Camera::bind()
{
	_blendEngine->bind();

	mask_engine->clear_buffer();
	mask_engine->get_disabledState()->bind(0);
	WorldViewer::bind();
}
