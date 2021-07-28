#include "Camera.h"

#include <iostream>

#include "BlendEngine.h"
#include "MaskEngine.h"

#include "../d3d/Buffer/VertexBuffer.h"
#include "../I3DObject/Cube/Cube.h"
#include "Types/Types.h"
#include <DirectXMath.h>

const static DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_BACKWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_LEFT_VECTOR = DirectX::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
const static DirectX::XMVECTOR DEFAULT_RIGHT_VECTOR = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

void Render::Camera::update_position()
{
	auto camPos = _transform.get_position();
	_xm_camPosition = DirectX::XMVectorSet(camPos.z, camPos.y, camPos.x, 0.f);
	_viewMatrix = create_view_matrix();
}

void Render::Camera::draw_object(I3DObject* object)
{
	auto worldMatrix = object->transform.get_world_matrix();
	_matrix_buffer_struct = { DirectX::XMMatrixTranspose(
		worldMatrix * _viewMatrix * _projectionMatrix
	) };
	matrix_buffer->update();
	object->draw();
}

DirectX::XMMATRIX Render::Camera::create_view_matrix()
{
	auto rotation = _rotation.get_rotation();
	
	auto camRotMatrix = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	auto camTarget = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, camRotMatrix);

	camTarget = DirectX::XMVectorAdd(camTarget, _xm_camPosition);
	
	auto upDir = DirectX::XMVector3TransformCoord(DEFAULT_UP_VECTOR, camRotMatrix);

	auto rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(0, rotation.y, 0);
	_forward_vector = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, rotationMatrix);
	_right_vector = DirectX::XMVector3TransformCoord(DEFAULT_RIGHT_VECTOR, rotationMatrix);
	_up_vector = DirectX::XMVector3TransformCoord(DEFAULT_UP_VECTOR, rotationMatrix);

	return DirectX::XMMatrixLookAtLH(
		_xm_camPosition,
		camTarget,
		upDir
	);
}

DirectX::XMMATRIX Render::Camera::create_proj_matrix()
{
	auto forRadians = (_fov / 360.f) * DirectX::XM_2PI;

	auto res = _context->get_screen_resolution();
	auto aspectRatio = res.width / res.height;

	return DirectX::XMMatrixPerspectiveFovLH(forRadians, aspectRatio, 0.1f, 120.f);
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
	using namespace DirectX;
	auto nigga = (_forward_vector * pos.x) + (_right_vector * pos.z) + (_up_vector * pos.y);
	
	XMFLOAT3 forw;
	XMStoreFloat3(&forw,nigga);
	_transform.adjust_position(Position3(forw.z, forw.y, forw.x));
	update_position();
}

void Render::Camera::adjust_rotation(Vector3 rot)
{
	_rotation.adjust_rotation(rot);
	_viewMatrix = create_view_matrix();
}

void Render::Camera::set_resolution(Surface new_resolution)
{
	std::cout << "NEW RESOLUTION: " << new_resolution.width << " " << new_resolution.height << '\n';
	//_b0_constant_buffer_struct.width = new_resolution.width;
	//_b0_constant_buffer_struct.height = new_resolution.height;
	control_buffer->update();
}

void Render::Camera::set_alpha(float alpha)
{
	_control_buffer_struct.opacity = alpha;
	control_buffer->update();
}

Canvas::Canvas2DLayer* Render::Camera::create_canvas_2d()
{
	auto* layer = new Canvas::Canvas2DLayer(_context);
	register_canvas_2d(layer);
	return layer;
}

void Render::Camera::register_canvas_2d(Canvas::Canvas2DLayer* layer)
{
	_canvas2DLayers.push_back(layer);
}

Core::GraphicsContext* Render::Camera::graphics_context()
{
	return _context;
}

ID3D11DeviceContext* Render::Camera::context() const
{
	return _context->context;
}

ID3D11Device* Render::Camera::device() const
{
	return _context->device;
}

ID3D11RenderTargetView* Render::Camera::get_target_view() const
{
	return _context->get_render_target_view();
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
	return _context->get_screen_resolution();
}

Render::Camera::Camera(Core::GraphicsContext* context)
	:
	_transform(Position3(-4.f, 0, 0)),
	_rotation(Vector3(0, 0, 0))
{
	_context = context;
	_blendEngine = new BlendEngine(_context);
	_maskEngine  = new MaskEngine(_context);
	_maskEngine->bind();
	
	auto resolution = context->get_screen_resolution();
	_matrix2d_buffer_struct = { DirectX::XMMatrixScaling(1.f / (resolution.width / 2),1.f / (resolution.height / 2),1.f) };
	matrix2d_buffer = new ConstantBuffer(_context, &_matrix2d_buffer_struct, sizeof(_matrix2d_buffer_struct), 0);

	matrix_buffer = new ConstantBuffer(_context, &_matrix_buffer_struct, sizeof(_matrix_buffer_struct), 0);
	matrix_buffer->update();

	control_buffer = new ConstantBuffer(context, &_control_buffer_struct, sizeof(_control_buffer_struct), 1);
	control_buffer->update();

	_projectionMatrix = create_proj_matrix();
	
	update_position();
}

void Render::Camera::present()
{
	_blendEngine->bind();
	_maskEngine->clear_buffer();


	matrix_buffer->bind();
	control_buffer->bind();
	
	_context->begin_3d();


	_control_buffer_struct.offset = Position2(0, 0);
	control_buffer->update();

	// render all world objects
	
	auto objects = _context->worldspace()->objects;
	for(auto*object : objects)
	{
		this->draw_object(object);
	}
	return;
	
	// then render canvas
	
	_context->begin_2d();
	_maskEngine->clear_buffer();

	matrix2d_buffer->bind();

	_control_buffer_struct.offset = Position2(-1, 1);
	control_buffer->update();

	DrawEvent2D event(this,nullptr);
	for(auto*layer : _canvas2DLayers)
	{
		event.layer = layer;
		event.set_alpha(1.f);
		
		layer->update();
		layer->render(&event);
	}
}
