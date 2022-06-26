#pragma once
#include <Types/Material.h>

#include "GraphicsCommon.h"
#include "Rasterizer.h"
#include "Texture.h"

namespace Render
{
	class __declspec(dllexport) IAllocator
	{
	public:
		virtual ~IAllocator() = default;

		virtual GEIndexBuffer* alloc_index_buffer(unsigned size) = 0;
		virtual GEIndexBuffer* alloc_index_buffer(void* data, unsigned size) = 0;

		GETexture* create_texture(Material& material);
		GETexture* create_texture(Material material);
		virtual GETexture* create_texture(ITexture2DDesc desc) =0;
		virtual GERasterizer create_rasterizer(RasterizerDesc desc)=0;
	};

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

