#include "SwapChainRenderTarget.h"
#include "../../Graphics.h"

Render::SwapChainRenderTarget::SwapChainRenderTarget(Core::GraphicsContext* context, IDXGISwapChain* swap)
	: IRenderTarget(context)
{
	ID3D11Resource* back_buffer;
	swap->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&back_buffer);

	D3D11_TEXTURE2D_DESC desc;
	((ID3D11Texture2D*)back_buffer)->GetDesc(&desc);

	context->device->CreateRenderTargetView(back_buffer, nullptr, &_targetView);
	_texture = Texture(context, (ID3D11Texture2D*)back_buffer);

	back_buffer->Release();
}
