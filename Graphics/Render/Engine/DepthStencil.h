#pragma once
#include <d3d11.h>

namespace Core
{
	class GraphicsContext;
}

namespace Render {
	enum class StencilUsage : __int8
	{
		none = 0,
		normal = 1,
		mask = 2,
		write = 3
	};

	struct __declspec(dllexport) DepthStencilDesc {
		bool depth = true;
		StencilUsage stencil_usage = StencilUsage::normal;

		DepthStencilDesc() = default;
		DepthStencilDesc(bool depth,StencilUsage stencil_usage)
			: depth(depth),
			stencil_usage(stencil_usage)
		{}
	};

	class __declspec(dllexport) DepthStencil final
	{
		ID3D11DeviceContext* _context;
		ID3D11DepthStencilState* _state;
	public:
		DepthStencil();
		DepthStencil(Core::GraphicsContext* context,DepthStencilDesc desc);

		void bind(unsigned reference = 0) const;
		bool valid() const;
	};
}
