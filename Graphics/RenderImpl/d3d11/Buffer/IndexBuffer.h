﻿#pragma once
#include <d3d11.h>

#include "../Bindable.h"
#include "../../../Graphics/IBuffers/IIndexBuffer.h"

namespace Render {
	class IndexBuffer : public IIndexBuffer
	{
		ID3D11Buffer* _index_buffer;
		UINT* _index;
		size_t _size;
	public:
		IndexBuffer(Core::GraphicsContext* graphics_context,UINT*index,size_t size);

		void bind() override;

		auto size() { return _size; }
		~IndexBuffer() override;
	};
}
