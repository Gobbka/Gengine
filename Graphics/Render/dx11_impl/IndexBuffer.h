#pragma once
#include <d3d11.h>

namespace Core
{
	class GraphicsContext;
}

namespace Render {
	class __declspec(dllexport) DX11IndexBuffer
	{
		Core::GraphicsContext* _context;
		size_t _size;
		unsigned* _data;
		ID3D11Buffer* _index_buffer;

	public:
		DX11IndexBuffer(Core::GraphicsContext* graphics_context,UINT*index,size_t size);

		void bind();
		void update();

		size_t get_size() const { return _size; }
		auto& operator[](unsigned index) const
		{
			return _data[index];
		}

		~DX11IndexBuffer();
	};
}
