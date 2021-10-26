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
		size_t size = 0;

	};

	class __declspec(dllexport) IVertexBuffer : public Bindable
	{
	protected:
		size_t size;

		IVertexBuffer(Core::GraphicsContext* engine, size_t size) : Bindable(engine), size(size), data(nullptr) {}
	public:
		Vertex* data;

		inline size_t get_size()
		{
			return size;
		}

		virtual void copy_to(IVertexBuffer* buffer) =0;
		virtual void copy_to(void* buffer, unsigned size) =0;

		virtual void update(unsigned update_size = -1) = 0;

		void count_normals(IIndexBuffer*buffer) const;

		Vertex& at(unsigned index) const;
	};
}
