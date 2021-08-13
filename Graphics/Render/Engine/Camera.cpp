#include "Camera.h"

#include "BlendEngine.h"
#include "MaskEngine.h"
#include "Types/Types.h"

#include <DirectXMath.h>
#include <iostream>

#include "../Events/RenderEvent.h"

const static DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_BACKWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_LEFT_VECTOR = DirectX::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_RIGHT_VECTOR = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

void Render::Camera::draw_object(Model* object, DrawEvent3D event3d)
{
	//auto modelMatrix = object->transform.get_world_matrix();
	//_matrix_buffer_struct = { DirectX::XMMatrixTranspose(
	//	modelMatrix * event3d.VPMatrix
	//) };
	//matrix_buffer->update();
	//object->draw(event3d);
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
	//_resolution = resolution;
	_matrix2d_buffer_struct = { DirectX::XMMatrixScaling(1.f / (resolution.width / 2),1.f / (resolution.height / 2),1.f) };
	//_projectionMatrix = create_proj_matrix();
	
	matrix2d_buffer->update();
}

void Render::Camera::set_alpha(float alpha)
{
	if (alpha == _control_buffer_struct.opacity)
		return;
	
	_control_buffer_struct.opacity = alpha;
	control_buffer->update();
}


Canvas::Canvas2DLayer* Render::Camera::create_canvas_2d()
{
	auto* layer = new Canvas::Canvas2DLayer(context);
	register_canvas_2d(layer);
	return layer;
}

void Render::Camera::register_canvas_2d(Canvas::Canvas2DLayer* layer)
{
	_canvas2DLayers.push_back(layer);
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

Render::MaskEngine* Render::Camera::mask_engine() const
{
	return _maskEngine;
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
	_maskEngine  = new MaskEngine(this);
	
	auto _resolution = get_view_resolution();
	_matrix2d_buffer_struct = { DirectX::XMMatrixScaling(1.f / (_resolution.width / 2),1.f / (_resolution.height / 2),1.f) };
	matrix2d_buffer = new ConstantBuffer(context, &_matrix2d_buffer_struct, sizeof(_matrix2d_buffer_struct), 0);

	matrix_buffer = new ConstantBuffer(context, &_matrix_buffer_struct, sizeof(_matrix_buffer_struct), 0);

	control_buffer = new ConstantBuffer(context, &_control_buffer_struct, sizeof(_control_buffer_struct), 1, ConstantBuffer::CBBindFlag_vs| ConstantBuffer::CBBindFlag_ps);
	
	update_position();
}

void Render::Camera::render()
{
	_cameraOptions.renderTarget->bind(_maskEngine->get_view());
	
	_blendEngine->bind();
	_maskEngine->set_state(_maskEngine->get_disabledState(),0,true);

	matrix_buffer->bind();
	control_buffer->bind();

	if(_cameraOptions.render_3d)
	{
		context->begin_3d();

		_control_buffer_struct.offset = Position2(0, 0);
		set_alpha(1.f);

		// render all world objects

		auto objects = context->worldspace()->objects;
		
		for (auto* object : objects)
		{
			auto modelMatrix = object->transform.get_world_matrix();
			_matrix_buffer_struct = { DirectX::XMMatrixTranspose(
				modelMatrix * _viewMatrix * _projectionMatrix
			) };
			matrix_buffer->update();
			
			this->view(object);
		}

		_maskEngine->clear_buffer();
	}
	
	if(_cameraOptions.render_2d)
	{
		// then render canvas

		context->begin_2d();

		matrix2d_buffer->bind();

		_control_buffer_struct.offset = Position2(-1, 1);
		_control_buffer_struct.opacity = 1.f;
		control_buffer->update();

		DrawEvent2D event(this, nullptr);
		for (auto* layer : _canvas2DLayers)
		{
			event.layer = layer;
			event.set_alpha(1.f);

			layer->update();
			layer->render(&event);
		}

		_maskEngine->clear_buffer();
	}
}
