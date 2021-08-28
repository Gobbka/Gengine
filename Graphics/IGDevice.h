#pragma once
#include "Ecs/Ecs.h"
#include "Graphics/IBuffers/IIndexBuffer.h"
#include "Graphics/IBuffers/IVertexBuffer.h"
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

		virtual Texture* create_texture(Material& material) =0;
	};
}

