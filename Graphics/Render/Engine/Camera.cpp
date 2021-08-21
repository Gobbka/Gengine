#include "Camera.h"

#include "BlendEngine.h"
#include "MaskEngine.h"
#include "Types/Types.h"

#include <DirectXMath.h>
#include <iostream>

#include "../Events/RenderEvent.h"
#include "../Light/DirectionLight.h"

const static DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_BACKWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_LEFT_VECTOR = DirectX::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_RIGHT_VECTOR = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

void Render::Camera::clear(Color3 color)
{
	render_target->clear(color);
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

void Render::Camera::set_alpha(float alpha)
{
	//if (alpha == control_buffer->data.opacity)
	//	return;
	//
	//control_buffer->data.opacity = alpha;
	//control_buffer->update();
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

	test_light = nullptr;
}

void Render::Camera::render()
{
	
	if(_cameraOptions.render_2d)
	{
		// then render canvas

		context->begin_2d();
		mask_engine->get_discardState()->bind(0);
		mask_engine->clear_buffer();
		
		//matrix2d_buffer->bind();

		//control_buffer->data.offset = Position2(-1, 1);
		//control_buffer->data.opacity = 1.f;
		//control_buffer->update();

		DrawEvent2D event(this, nullptr);
		for (auto* layer : _canvas2DLayers)
		{
			event.layer = layer;
			event.set_alpha(1.f);

			layer->update();
			layer->render(&event);
		}

		mask_engine->clear_buffer();
	}
}

void Render::Camera::bind()
{
	render_target->bind(mask_engine->get_view());

	_blendEngine->bind();

	mask_engine->clear_buffer();
	mask_engine->get_disabledState()->bind(0);
}
