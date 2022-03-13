#pragma once
#include <d3d11.h>
#include "../Common/IAllocator.h"

namespace Render
{
	class __declspec(dllexport) DX11Allocator final : public IAllocator
	{
		ID3D11Device* _device;
		GEGraphics* _gfx;

		IVertexBuffer<char>* alloc_vertex_buffer_impl(void* data, UINT element_size, IVertexBufferDesc desc) override;
	public:
		DX11Allocator(ID3D11Device* device, GEGraphics*context);

		GEIndexBuffer* alloc_index_buffer(unsigned size) override;
		GEIndexBuffer* alloc_index_buffer(void* data, unsigned size) override;

		GETexture* create_texture(ITexture2DDesc desc) override;
		GERasterizer create_rasterizer(RasterizerDesc desc) override;
	};
}
