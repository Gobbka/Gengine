#pragma once
#include <d3d11.h>
#include "../Common/IGDevice.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class __declspec(dllexport) D11GDevice final : public IGDevice
	{
		ID3D11Device* _device;
		Core::GraphicsContext* _gfx;

		IVertexBuffer<char>* alloc_vertex_buffer_impl(void* data, UINT element_size, IVertexBufferDesc desc) override;
	public:
		D11GDevice(ID3D11Device* device,Core::GraphicsContext*context);

		GEIndexBuffer* alloc_index_buffer(unsigned size) override;
		GEIndexBuffer* alloc_index_buffer(void* data, unsigned size) override;

		GETexture* create_texture(ITexture2DDesc desc) override;
		GERasterizer create_rasterizer(RasterizerDesc desc) override;
	};
}
