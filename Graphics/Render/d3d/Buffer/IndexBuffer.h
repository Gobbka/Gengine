#pragma once
#include <d3d11.h>
#include "../../../Graphics/IBuffers/IIndexBuffer.h"

namespace Render {
	class IndexBuffer : public IIndexBuffer
	{
		ID3D11Buffer* _index_buffer;
		
	public:
		IndexBuffer(Core::GraphicsContext* graphics_context,UINT*index,size_t size);

		void bind() override;
		void update() override;
		~IndexBuffer() override;
	};
}
