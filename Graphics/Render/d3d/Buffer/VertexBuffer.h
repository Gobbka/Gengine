#pragma once
#include <d3d11.h>
#include "../../Common/IVertexBuffer.h"

namespace Render
{
	struct Vertex;

	class VertexBuffer : public IVertexBuffer<char>
	{
	private:
		ID3D11Buffer* _buffer = nullptr;
	public:
		void copy_to(IVertexBuffer* buffer) override;
		void copy_to(void* buffer, UINT size) override;
	public:
		
		VertexBuffer(Core::GraphicsContext* engine, Vertex* data,size_t length, ID3D11Buffer*buffer);
		~VertexBuffer() override;

		void bind() override;
		void update(UINT update_size = -1) override;
	};
}
