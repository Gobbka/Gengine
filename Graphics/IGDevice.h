#pragma once
#include <Types/Material.h>
#include "Graphics/IBuffers/IIndexBuffer.h"
#include "Graphics/IBuffers/IVertexBuffer.h"
#include "Render/d3d/Vertex.h"
#include "Render/d3d/Buffer/Texture.h"
#include "Render/Engine/Rasterizer.h"

namespace Render
{
	class Material;
	class RenderTarget;

	class __declspec(dllexport) IGDevice
	{
	protected:
		virtual IVertexBuffer* alloc_vertex_buffer_impl(void*data,size_t element_size, IVertexBufferDesc desc) = 0;
	public:
		virtual ~IGDevice() = default;

		virtual IVertexBuffer* alloc_vertex_buffer(unsigned size, bool dynamic = true);
		virtual IVertexBuffer* alloc_vertex_buffer(Vertex* data, IVertexBufferDesc desc);

		virtual IIndexBuffer* alloc_index_buffer(unsigned size) = 0;
		virtual IIndexBuffer* alloc_index_buffer(void* data, unsigned size) = 0;

		Texture* create_texture(Material& material);
		virtual Texture* create_texture(ITexture2DDesc desc) =0;
		virtual Rasterizer create_rasterizer(RasterizerDesc desc)=0;
	};

	inline IVertexBuffer* IGDevice::alloc_vertex_buffer(unsigned size, bool dynamic)
	{
		IVertexBufferDesc buffer_desc;
		buffer_desc.length = size;
		buffer_desc.usage = dynamic ? IVertexBufferDesc::Usage::dynamic : IVertexBufferDesc::Usage::classic;
		return alloc_vertex_buffer_impl(new Vertex[size], sizeof(Vertex), buffer_desc);
	}

	inline IVertexBuffer* IGDevice::alloc_vertex_buffer(Vertex* data, IVertexBufferDesc desc)
	{
		return alloc_vertex_buffer_impl(data, sizeof(Vertex), desc);
	}

	inline Texture* IGDevice::create_texture(Material& material)
	{
		ITexture2DDesc desc;
		desc.format = material.format;
		desc.height = (UINT)material.height();
		desc.width  = (UINT)material.width();
		desc.rows   = 0;
		desc.stride = 0;
		desc.pSysMem = material.pSysMem();
		return this->create_texture(desc);
	}
}

