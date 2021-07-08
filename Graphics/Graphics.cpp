#include "Graphics.h"

#include <d3dcompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

#include "Canvas/CanvasLayer.h"
#include "Graphics/Types.h"
#include "Render/Engine/D3DEngine.h"
#include "Render/d3d/Buffer/VertexBuffer.h"

Core::GraphicsContext::GraphicsContext(ID3D11Device* dev, IDXGISwapChain* swap, ID3D11DeviceContext* context)
	: _screen_resolution(0,0)
{
	_device = dev;
	_swap = swap;
	_context = context;

	RECT window_rect;

	{
		DXGI_SWAP_CHAIN_DESC desc;
		swap->GetDesc(&desc);
		GetClientRect(desc.OutputWindow, &window_rect);
	}

	_screen_resolution = Surface(window_rect);
	
	ID3D11Resource* back_buffer;
	_swap->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&back_buffer);
	assert(SUCCEEDED(_device->CreateRenderTargetView(back_buffer, nullptr, &_targetView)));
	back_buffer->Release();

	_engine = new Render::D3DEngine(this);
	
	ID3DBlob* blob;
	assert(SUCCEEDED(D3DReadFileToBlob(L"C:\\Users\\Gobka\\source\\repos\\Gengine\\out\\shaders.cso", &blob)));

	assert(SUCCEEDED(_device->CreateVertexShader((const void*)blob->GetBufferPointer(), (size_t)blob->GetBufferSize(), nullptr, &_vertexShader)));

	HRESULT hr = _device->CreateInputLayout(
		Render::Layout,
		ARRAYSIZE(Render::Layout),
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&_inputLayout
	);

	blob->Release();

	assert(SUCCEEDED( D3DReadFileToBlob(L"C:\\Users\\Gobka\\source\\repos\\Gengine\\out\\pixel_shader.cso", &blob)));
	assert(SUCCEEDED( _device->CreatePixelShader((const void*)blob->GetBufferPointer(), (size_t)blob->GetBufferSize(), nullptr, &_pixelShader)));

	_viewport.Width = _screen_resolution.width;
	_viewport.Height = _screen_resolution.height;
	_viewport.MaxDepth = 1;
	_viewport.MinDepth = 1;
	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;
	_context->RSSetViewports(1, &_viewport);
}

ID3D11Device* Core::GraphicsContext::device() const
{
	return _device;
}

ID3D11DeviceContext* Core::GraphicsContext::context() const
{
	return _context;
}

Surface Core::GraphicsContext::get_screen_resolution() const
{
	return _screen_resolution;
}

ID3D11RenderTargetView* Core::GraphicsContext::get_render_target_view()
{
	return _targetView;
}

Render::D3DEngine* Core::GraphicsContext::get_2d_engine()
{
	return _engine;
}

Canvas::Canvas2DLayer* Core::GraphicsContext::create_2d_layer()
{
	auto* layer = new Canvas::Canvas2DLayer(_engine);
	append_2d_layer(layer);
	return layer;
}

void Core::GraphicsContext::append_2d_layer(Canvas::Canvas2DLayer*layer)
{
	_2d_layers.push_back(layer);
}

void Core::GraphicsContext::set_resolution(Surface new_resolution)
{
	_screen_resolution = new_resolution;
	_engine->set_resolution(new_resolution);
}

void Core::GraphicsContext::clear()
{
	float color[4]{ RGB_TO_FLOAT(31,31,32) ,1.f };
	_context->ClearRenderTargetView(_targetView, color);
}

void Core::GraphicsContext::present() const
{
	_context->RSSetViewports(1, &_viewport);
	_context->OMSetRenderTargets(1, &_targetView, nullptr);
	_context->IASetInputLayout(_inputLayout);
	
	_context->VSSetShader(_vertexShader, nullptr, 0);
	_context->PSSetShader(_pixelShader, nullptr, 0);


	_context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	Render::DrawEvent draw_event(_engine,nullptr);
	
	for(auto* layer2d : _2d_layers)
	{
		draw_event.layer = layer2d;
		
		layer2d->update();
		layer2d->canvas()->get_vbuffer()->bind();
		
		_engine->present(&draw_event);
	}
	_swap->Present(1u, 0u);
}

Core::GraphicsContext* Core::GraphicsContext::new_context(HWND hwnd)
{
	IDXGISwapChain* pswap;
	ID3D11Device* device;
	ID3D11DeviceContext* context;

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc = DXGI_MODE_DESC{
		800,600,
		{0,0},
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
	
	assert(SUCCEEDED (D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_REFERENCE,
		//D3D_DRIVER_TYPE_HARDWARE,
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
	)));

	return new GraphicsContext(device, pswap, context);
}
