#include "Graphics.h"

#include <d3dcompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

#include <iostream>

#include "Canvas/CanvasLayer.h"
#include "Types/Types.h"
#include "Render/d3d/Buffer/Texture.h"
#include "Render/Engine/Camera.h"

#include "Render/d3d/Shader/SamplerState.h"
#include "Render/d3d/Shader/PixelShader.h"
#include "Render/d3d/Shader/VertexShader.h"

#include "Graphics/Material/Material.h"

void Core::WorldSpace::add_object(Render::I3DObject* object)
{
	objects.push_back(object);
}

Core::GraphicsContext::GraphicsContext(ID3D11Device* dev, IDXGISwapChain* swap, ID3D11DeviceContext* context)
	: _screen_resolution(0,0)
{
	device = dev;
	_swap = swap;
	this->context = context;

	{
		DXGI_SWAP_CHAIN_DESC desc;
		swap->GetDesc(&desc);
		_screen_resolution = Surface(desc.BufferDesc.Width,desc.BufferDesc.Height);
	}
	
	ID3D11Resource* back_buffer;
	_swap->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&back_buffer);
	
	assert(back_buffer != nullptr);
	assert(SUCCEEDED(device->CreateRenderTargetView(back_buffer, nullptr, &_targetView)));
	
	back_buffer->Release();

	_main_camera = new Render::Camera(this);

	_samplerState = new Render::SamplerState(this);
	
	_vertexShader = new Render::VertexShader(this);
	_pixelShader  = new Render::PixelShader(this);
	_vertexShader3d = new Render::VertexShader(this);

	auto* _texture_ps = new Render::PixelShader(this);
	auto* _texture_vs = new Render::VertexShader(this);
	ID3D11InputLayout* _texture_layout=nullptr;

	
	_vertexShader->read_file(L"d3d11\\shaders.cso");
	_vertexShader->create_input_layout(Render::VertexLayout, ARRAYSIZE(Render::VertexLayout), &_inputLayout);
	_vertexShader->release_blob();

	_vertexShader3d->read_file(L"d3d11\\vertex_3d_vs.cso");
	_vertexShader3d->release_blob();

	_pixelShader->read_file(L"d3d11\\pixel_shader.cso");
	_pixelShader->release_blob();


	_texture_vs->read_file(L"d3d11\\texture_vs.cso");
	_texture_vs->create_input_layout(Render::TextureLayout, ARRAYSIZE(Render::TextureLayout), &_texture_layout);
	_texture_vs->release_blob();

	_texture_ps->read_file(L"d3d11\\texture_ps.cso");
	_texture_ps->release_blob();

	_spriteEngine = new Render::SpriteEngine(this, _texture_ps, _texture_vs, _texture_layout);
	
	_viewport.Width  = _screen_resolution.width;
	_viewport.Height = _screen_resolution.height;
	_viewport.MaxDepth = 1;
	_viewport.MinDepth = 0;
	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;
	context->RSSetViewports(1, &_viewport);

	_samplerState->bind();
}

Core::WorldSpace* Core::GraphicsContext::worldspace()
{
	return &_worldSpace;
}

Render::SpriteEngine* Core::GraphicsContext::get_sprite_engine()
{
	return _spriteEngine;
}

Surface Core::GraphicsContext::get_screen_resolution() const
{
	return _screen_resolution;
}

ID3D11RenderTargetView* Core::GraphicsContext::get_render_target_view()
{
	return _targetView;
}

Render::Camera* Core::GraphicsContext::main_camera()
{
	return _main_camera;
}

bool Core::GraphicsContext::create_buffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buffer) const
{
	return SUCCEEDED(device->CreateBuffer(desc, data, buffer));
}

void Core::GraphicsContext::set_resolution(Surface new_resolution)
{
	_screen_resolution = new_resolution;
	_main_camera->set_resolution(new_resolution);
}

void Core::GraphicsContext::clear(Color3 color)
{
	auto float_color = Color4(color).to_float4();
	context->ClearRenderTargetView(_targetView, (FLOAT*)&float_color);
}

void Core::GraphicsContext::present() const
{
	context->RSSetViewports(1, &_viewport);
	//context->OMSetRenderTargets(1, &_targetView, nullptr);
	//context->IASetInputLayout(_inputLayout);
	
	context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//_context->IASetInputLayout(_texture_layout);
	//_samplerState->bind();

	//_texture_ps->bind();
	//_texture_vs->bind();

	_main_camera->present();

	_swap->Present(1u, 0u);
}

void Core::GraphicsContext::begin_2d()
{
	context->IASetInputLayout(_inputLayout);
	_vertexShader->bind();
	_pixelShader->bind();
}

void Core::GraphicsContext::begin_3d()
{
	_vertexShader3d->bind();
	_pixelShader->bind();
	context->IASetInputLayout(_inputLayout);
}

Render::Texture* Core::GraphicsContext::create_texture(Render::Material* material)
{
	return new Render::Texture(this, *material);
}

void Core::GraphicsContext::set_texture(Render::Texture* texture)
{
	texture->bind();
}

Core::GraphicsContext* Core::GraphicsContext::new_context(HWND hwnd,Surface size)
{
	IDXGISwapChain* pswap=nullptr;
	ID3D11Device* device=nullptr;
	ID3D11DeviceContext* context=nullptr;

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc = DXGI_MODE_DESC{
		(UINT)size.width,(UINT)size.height,
		{60,1},
		DXGI_FORMAT_B8G8R8A8_UNORM,
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
		DXGI_MODE_SCALING_UNSPECIFIED
	};
	sd.SampleDesc = { 1,0 };
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.BufferCount = 1;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;
	
	auto hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
	#ifdef _DEBUG
		//D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_HARDWARE,
	#else
		D3D_DRIVER_TYPE_HARDWARE,
	#endif
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pswap,
		&device,
		nullptr,
		&context
	);
	
	assert(SUCCEEDED(hr));

	return new GraphicsContext(device, pswap, context);
}
