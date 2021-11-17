#pragma once
#include "../../Render/d3d/Bindable.h"

namespace Render
{
	class IIndexBuffer;
	struct Vertex;

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
	class __declspec(dllexport) IVertexBuffer : public Bindable
	{
	protected:
		size_t size;

		IVertexBuffer(Core::GraphicsContext* engine,T*data, size_t size) : Bindable(engine), size(size), data(data), stride_size(sizeof(T)) {}
	public:
		T* data;
		char stride_size;

		virtual void copy_to(IVertexBuffer* buffer) =0;
		virtual void copy_to(void* buffer, unsigned size) =0;

		virtual void update(unsigned update_size = -1) = 0;

		inline size_t get_size()
		{
			return size;
		}

		T& at(unsigned index) const
		{
			return data[index];
		}
	};
}
