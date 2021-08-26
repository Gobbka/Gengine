#pragma once
#include "../../Render/d3d/Bindable.h"

namespace Render
{
	class IIndexBuffer : public Bindable
	{
	protected:
		size_t size;
		UINT* data;
	public:
		IIndexBuffer(Core::GraphicsContext* context,size_t size,UINT*data) : Bindable(context)
		{
			this->size = size;
			this->data = data;
		}

		size_t get_size() const { return size; }
	};
}
