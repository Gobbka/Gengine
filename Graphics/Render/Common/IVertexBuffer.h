#pragma once
#include "GraphicsCommon.h"

namespace Render
{
	struct __declspec(dllexport) IVertexBufferDesc {
		enum class Usage
		{
			classic,
			immutable,
			dynamic
		}   usage = Usage::classic;
		size_t length = 0;
	};

	template<typename T>
	class __declspec(dllexport) IVertexBuffer
	{
	protected:
		GEGraphics* _graphics;
		size_t size;

		IVertexBuffer(GEGraphics* graphics,T*data, size_t size)
			: _graphics(graphics)
			, size(size)
			, data(data)
			, stride_size(sizeof(T))
		{}

	public:
		T* data;
		char stride_size;

		virtual void copy_to(IVertexBuffer* buffer) =0;
		virtual void copy_to(void* buffer, unsigned size) =0;

		virtual void update(unsigned update_size = -1) = 0;
		virtual void bind() = 0;
		virtual ~IVertexBuffer() = default;

		size_t get_size()
		{
			return size;
		}

		T& at(unsigned index) const
		{
			return data[index];
		}
	};
}
