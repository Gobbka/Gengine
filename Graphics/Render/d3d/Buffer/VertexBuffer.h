#pragma once
#include <d3d11.h>
#include "../../../Graphics/IBuffers/IVertexBuffer.h"

namespace Render
{
	struct Vertex;

	class VertexBuffer : public IVertexBuffer
	{
	private:
		ID3D11Buffer* _buffer = nullptr;
	public:
		void copy_to(IVertexBuffer* buffer) override;
		void copy_to(void* buffer, UINT size) override;
	public:
		
		VertexBuffer(Core::GraphicsContext* engine, Vertex* data, UINT size, bool dynamic = true);
		~VertexBuffer() override;

		void bind() override;
		void update(UINT update_size = -1) override;
	};
}
