#pragma once
#include "../../Render/d3d/Bindable.h"

namespace Render
{
	struct Vertex;

	class __declspec(dllexport) IVertexBuffer : public Bindable
	{
	protected:
		size_t size;
	public:
		Vertex* data;
		
		IVertexBuffer(Core::GraphicsContext* engine,size_t size) : Bindable(engine),size(size),data(nullptr) {}

		inline size_t get_size()
		{
			return size;
		}

		virtual void copy_to(IVertexBuffer* buffer) =0;
		virtual void copy_to(void* buffer, UINT size) =0;

		virtual void update(unsigned update_size = -1) = 0;
	};
}
