#pragma once
#include "Graphics/IBuffers/IIndexBuffer.h"
#include "Graphics/IBuffers/IVertexBuffer.h"
#include <Types/Material.h>
#include "Render/d3d/Buffer/Texture.h"

namespace Render
{
	class Material;
	class RenderTarget;

	class __declspec(dllexport) IGDevice
	{
	public:
		virtual ~IGDevice() = default;

		virtual IVertexBuffer* alloc_vertex_buffer(unsigned size, bool dynamic = true) = 0;
		virtual IVertexBuffer* alloc_vertex_buffer(void* data, unsigned size, bool dynamic = true) = 0;

		virtual IIndexBuffer* alloc_index_buffer(unsigned size) = 0;
		virtual IIndexBuffer* alloc_index_buffer(void* data, unsigned size) = 0;

		Texture* create_texture(Material& material);
		virtual Texture* create_texture(ITexture2DDesc desc) =0;
		
	};
	
	inline Texture* IGDevice::create_texture(Material& material)
	{
		ITexture2DDesc desc;
		desc.format = material.format;
		desc.height = material.height();
		desc.width = material.width();
		desc.rows = 0;
		desc.stride = 0;
		desc.pSysMem = material.pSysMem();
		return this->create_texture(desc);
	}
}

