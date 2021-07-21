#pragma once
#include <d3d11.h>

#include "../Bindable.h"

namespace Render {
	class IndexBuffer : public Bindable
	{
		ID3D11Buffer* _index_buffer;
		UINT* _index;
	public:
		IndexBuffer(Core::GraphicsContext* graphics_context,UINT*index,size_t size);

		void bind() override;
	};
}
