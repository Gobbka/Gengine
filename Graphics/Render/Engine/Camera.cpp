#include "Camera.h"

#include <iostream>

#include "../../Graphics/Types.h"
#include "BlendEngine.h"
#include "MaskEngine.h"
#include "../d3d/Buffer/VertexBuffer.h"
#include "../I3DObject/Cube/Cube.h"


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
	: _camPosition(DirectX::XMVectorSet(0,0,-4.f,0)),
	  _lookAt(DirectX::XMVectorSet(0.f,0.f,0.f,0.f))
{
	_context = context;
	_blendEngine = new BlendEngine(_context);
	_maskEngine  = new MaskEngine(_context);
	
	_b0_constant_buffer_struct = { 800,600,0.5 };

	b0_buffer = new ConstantBuffer(_context, &_b0_constant_buffer_struct, sizeof(_b0_constant_buffer_struct), 0);
	b0_buffer->update();

	_b1_constant_buffer_struct = { DirectX::XMMatrixTranspose( DirectX::XMMatrixRotationRollPitchYaw(0,35,0) )};

	matrix_buffer = new ConstantBuffer(context, &_b1_constant_buffer_struct, sizeof(_b1_constant_buffer_struct), 0);
	matrix_buffer->update();

	_cube = new Cube(_context);

	
}

void Render::Camera::present(DrawEvent* event)
{
	_blendEngine->bind();
	//_maskEngine->bind();
	{
		static float gakba = 0.0f;
		auto worldMatrix = DirectX::XMMatrixIdentity();
		auto viewMatrix = DirectX::XMMatrixLookAtLH(_camPosition, _lookAt, DirectX::XMVectorSet(0, 1.f, 0, 0));

		auto forRadians = (_fov / 360.f) * DirectX::XM_2PI;
		auto aspectRatio = 1400.f / 780.f;

		auto projMatrix = DirectX::XMMatrixPerspectiveFovLH(forRadians, aspectRatio, 0.1f, 1000.f);
		
		_b1_constant_buffer_struct = { DirectX::XMMatrixTranspose(worldMatrix * viewMatrix * projMatrix )};
		matrix_buffer->update();
		gakba += 0.01f;
	}
	_context->begin_3d();
	matrix_buffer->bind();
	_cube->draw();
	// render all world objects
	
	// then render canvas
	_context->begin_2d();
	b0_buffer->bind();

	for(auto*layer : _canvas2DLayers)
	{
		event->layer = layer;

		layer->update();
		layer->canvas()->get_vbuffer()->bind();
		
		layer->render(event);
	}
	//event->layer->render(event);
}
