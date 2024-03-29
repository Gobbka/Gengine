﻿#pragma once
#include <Types/Material.h>

#include "GraphicsCommon.h"
#include "IVertexBuffer.h"
#include "Rasterizer.h"
#include "Texture.h"

namespace Render
{
	class __declspec(dllexport) IAllocator
	{
	protected:
		virtual IVertexBuffer<char>* alloc_vertex_buffer_impl(void*data,UINT element_size, IVertexBufferDesc desc) = 0;
	public:
		virtual ~IAllocator() = default;

		template<typename T>
		IVertexBuffer<T>* alloc_vertex_buffer(unsigned size, bool dynamic = true);
		template<typename T>
		IVertexBuffer<T>* alloc_vertex_buffer(T* data, IVertexBufferDesc desc);

		virtual GEIndexBuffer* alloc_index_buffer(unsigned size) = 0;
		virtual GEIndexBuffer* alloc_index_buffer(void* data, unsigned size) = 0;

		GETexture* create_texture(Material& material);
		GETexture* create_texture(Material material);
		virtual GETexture* create_texture(ITexture2DDesc desc) =0;
		virtual GERasterizer create_rasterizer(RasterizerDesc desc)=0;
	};

	template <typename T>
	IVertexBuffer<T>* IAllocator::alloc_vertex_buffer(unsigned size, bool dynamic)
	{
		IVertexBufferDesc buffer_desc;
		buffer_desc.length = size;
		buffer_desc.usage = dynamic ? IVertexBufferDesc::Usage::dynamic : IVertexBufferDesc::Usage::classic;
		auto* buffer = (IVertexBuffer<T>*)alloc_vertex_buffer_impl(new T[size], sizeof(T), buffer_desc);
		buffer->stride_size = sizeof(T);

		return buffer;
	}

	template <typename T>
	IVertexBuffer<T>* IAllocator::alloc_vertex_buffer(T* data, IVertexBufferDesc desc)
	{
		auto* buffer = (IVertexBuffer<T>*)alloc_vertex_buffer_impl(data, sizeof(T), desc);
		buffer->stride_size = sizeof(T);
		return buffer;
	}

	inline GETexture* IAllocator::create_texture(Material& material)
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

	inline GETexture* IAllocator::create_texture(Material material)
	{
		ITexture2DDesc desc;
		desc.format = material.format;
		desc.height = (UINT)material.height();
		desc.width = (UINT)material.width();
		desc.rows = 0;
		desc.stride = 0;
		desc.pSysMem = material.pSysMem();
		return this->create_texture(desc);
	}
}

