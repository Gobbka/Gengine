#pragma once
#include <d3d11.h>
#include "../Bindable.h"

namespace Render
{
	struct Vertex;

	class __declspec(dllexport) VertexBuffer : public Bindable
	{
	private:
		ID3D11Buffer* _buffer = nullptr;
	public:
		Vertex* data = nullptr;
		UINT size = 0;

		void copy_to(VertexBuffer* buffer) const;
		void copy_to(void* buffer, UINT size) const;
	public:
		static VertexBuffer* alloc(Core::GraphicsContext* engine, UINT size, bool dynamic = true);
		
		VertexBuffer(Core::GraphicsContext* engine, Vertex* data, UINT size, bool dynamic = true);
		~VertexBuffer() override;

		void bind() override;
		void update(UINT update_size = -1);
	};
}
