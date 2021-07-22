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
}

void Render::Camera::set_resolution(Surface new_resolution)
{
	std::cout << "NEW RESOLUTION: " << new_resolution.width << " " << new_resolution.height << '\n';
	_b0_constant_buffer_struct.width = new_resolution.width;
	_b0_constant_buffer_struct.height = new_resolution.height;
	b0_buffer->update();
}

void Render::Camera::set_alpha(float alpha)
{
	_b0_constant_buffer_struct.alpha = alpha;
	b0_buffer->update();
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
	return _context->context();
}

ID3D11Device* Render::Camera::device() const
{
	return _context->device();
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
	
	auto resolution = context->get_screen_resolution();
	_b0_constant_buffer_struct = { resolution.width,resolution.height,0.5 };

	b0_buffer = new ConstantBuffer(_context, &_b0_constant_buffer_struct, sizeof(_b0_constant_buffer_struct), 0);
	b0_buffer->update();

	_b1_constant_buffer_struct = { DirectX::XMMatrixTranspose( DirectX::XMMatrixRotationRollPitchYaw(0,35,0) )};

	matrix_buffer = new ConstantBuffer(context, &_b1_constant_buffer_struct, sizeof(_b1_constant_buffer_struct), 0);
	matrix_buffer->update();

	_cube = new Cube(Position3(-.5f,0.5f,0),_context);
	_secondCube = new Cube({ -5.f,0.5f,0 }, _context);

	update_position();
}

void Render::Camera::present(DrawEvent* event)
{
	_blendEngine->bind();
	//_maskEngine->bind();
	{
		
		auto worldMatrix = DirectX::XMMatrixIdentity();

		auto viewMatrix = create_view_matrix();

		auto forRadians = (_fov / 360.f) * DirectX::XM_2PI;

		auto res = _context->get_screen_resolution(); 
		auto aspectRatio = res.width / res.height;

		auto projMatrix = DirectX::XMMatrixPerspectiveFovLH(forRadians, aspectRatio, 0.1f, 120.f);
		
		_b1_constant_buffer_struct = { DirectX::XMMatrixTranspose(worldMatrix * viewMatrix * projMatrix )};
		matrix_buffer->update();
	}
	_context->begin_3d();
	matrix_buffer->bind();
	_cube->draw();
	_secondCube->draw();
	// render all world objects
	
	// then render canvas
	_context->begin_2d();
	b0_buffer->bind();
	return;
	for(auto*layer : _canvas2DLayers)
	{
		event->layer = layer;

		layer->update();
		layer->canvas()->get_vbuffer()->bind();
		
		layer->render(event);
	}
	//event->layer->render(event);
}
