#include "Graphics.h"
#pragma comment(lib,"d3d11.lib")

#include "Graphics/Types.h"
#include "Render/Engine/D3DEngine.h"

Core::GraphicsContext::GraphicsContext(ID3D11Device* dev, IDXGISwapChain* swap, ID3D11DeviceContext* context)
{
	_device = dev;
	_swap = swap;
	_context = context;
	
	ID3D11Resource* back_buffer;
	_swap->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&back_buffer);
	_device->CreateRenderTargetView(back_buffer, nullptr, &_targetView);
	back_buffer->Release();

	_engine = new Render::D3DEngine(this);
}

ID3D11Device* Core::GraphicsContext::device() const
{
	return _device;
}

ID3D11DeviceContext* Core::GraphicsContext::context() const
{
	return _context;
}

void Core::GraphicsContext::clear()
{
	float color[4]{ RGB_TO_FLOAT(31,31,32) ,1.f };
	_context->ClearRenderTargetView(_targetView, color);
}

void Core::GraphicsContext::present() const
{
	Render::DrawEvent draw_event(nullptr);
	
	for(auto* layer2d : _2d_layers)
	{
		draw_event.layer = layer2d;
		
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
		0,0,
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
	
	if(FAILED (D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pswap,
		&device,
		nullptr,
		&context
	)))
	{
		MessageBox(0, L"CANNOT CREATE DEVICE", L"D3D ERROR", MB_ICONERROR);
	}

	return new GraphicsContext(device, pswap, context);
}
