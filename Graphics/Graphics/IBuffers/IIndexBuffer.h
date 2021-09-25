#pragma once
#include "../../Render/d3d/Bindable.h"

namespace Render
{
	class IIndexBuffer : public Bindable
	{
	protected:
		size_t size;
		unsigned* data;
	public:
		auto& operator[](unsigned index) const
		{
			return data[index];
		}
		
		IIndexBuffer(Core::GraphicsContext* context,size_t size,unsigned*data) : Bindable(context)
		{
			this->size = size;
			this->data = data;
		}
		IIndexBuffer() = delete;

		virtual void update() = 0;

		size_t get_size() const { return size; }
	};
}
