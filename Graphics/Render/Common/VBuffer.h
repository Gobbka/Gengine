#pragma once
#include "GraphicsCommon.h"

#ifdef DRAW_LIBRARY_DX11
#include "../dx11_impl/DX11VBuffer.h"
#endif

namespace Render
{
	template<typename T>
	class GEVBuffer : public GEVBuffer_Impl
	{
	public:
		GEVBuffer(GEGraphics* graphics,size_t length,bool dynamic = true)
			: DX11VBuffer(graphics,VBufferDesc{
				dynamic ? VBufferDesc::Usage::dynamic : VBufferDesc::Usage::classic,
				length,
				sizeof(T),
				nullptr
			})
		{
		}

		GEVBuffer(GEGraphics* graphics, VBufferDesc v_desc)
			: DX11VBuffer(graphics, v_desc)
		{
		}

		T& at(size_t index)
		{
			return ((T*)desc.p_data)[0];
		}
	};
}
