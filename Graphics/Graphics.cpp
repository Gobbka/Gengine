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
#include "Render/d3d/Buffer/D3D11BufferAllocator.h"

void Core::WorldSpace::add_object(Render::Model* object)
{
	objects.push_back(object);
}

Core::GraphicsContext::GraphicsContext(ID3D11Device* dev, IDXGISwapChain* swap, ID3D11DeviceContext* context)
	: _screen_resolution(0,0),
	device(dev),
	context(context),
	_targetView(this,swap)
{
	device = dev;
	_swap = swap;
	this->context = context;

	{
		DXGI_SWAP_CHAIN_DESC desc;
		swap->GetDesc(&desc);
		_screen_resolution = Surface(desc.BufferDesc.Width,desc.BufferDesc.Height);
	}

	_bufferAllocator = new Render::D3D11BufferAllocator(this);

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

Render::IBufferAllocator* Core::GraphicsContext::buffer_allocator() const
{
	return _bufferAllocator;
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

Render::RenderTarget* Core::GraphicsContext::get_render_target_view()
{
	return &_targetView;
}

Render::Camera* Core::GraphicsContext::create_camera(Render::RenderTarget* target)
{
	return target == nullptr ?
		new Render::Camera(this, &_targetView) :
		new Render::Camera(this,target);
}

void Core::GraphicsContext::set_resolution(Surface new_resolution)
{
	_screen_resolution = new_resolution;

	_viewport.Width = _screen_resolution.width;
	_viewport.Height = _screen_resolution.height;

	// TODO: make draw event where pass screen resolution
	//_main_camera->set_resolution(new_resolution);
}

void Core::GraphicsContext::clear(Color3 color)
{
	_targetView.clear(color);
}

void Core::GraphicsContext::new_frame()
{
	clear(Color3::black());
	context->RSSetViewports(1, &_viewport);
	context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void Core::GraphicsContext::present_frame()
{
	//if (_texture != nullptr)
	//{
	//	//D3D11_TEXTURE2D_DESC viewDesc;
	//	//D3D11_TEXTURE2D_DESC textureDesc;

	//	//((ID3D11Texture2D*)_targetView.get_resource())->GetDesc(&viewDesc);
	//	//_texture->get_texture()->GetDesc(&textureDesc);
	//	//
	//	//_texture->copy_to(_targetView.get_resource());
	//	//_textureTarget->clear(Color3(0.2f,0.2f,0.2f));
	//	//_main_camera->render({false,true,true,_textureTarget});
	//	//_buffer_texture->copy_to(_texture);

	//}
	////
	///

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
	_texture = texture;

	//D3D11_TEXTURE2D_DESC texture_desc;
	//texture_desc.BindFlags = D3D11_BIND_RENDER_TARGET;
	//texture_desc.Width = texture->width;
	//texture_desc.Height = texture->height;
	//texture_desc.MipLevels = 1;
	//texture_desc.ArraySize = 1;
	//texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//texture_desc.SampleDesc = { 1,0 };
	//texture_desc.CPUAccessFlags = 0;
	//texture_desc.MiscFlags = 0;
	//texture_desc.Usage = D3D11_USAGE_DEFAULT;
	//
	//ID3D11Texture2D* render_texture;
	//device->CreateTexture2D(&texture_desc, nullptr, &render_texture);
	//_buffer_texture = new Render::Texture(this, render_texture);
	//
	//_textureTarget = new Render::RenderTarget(this,_buffer_texture);
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
