#pragma once
#include <d3d11.h>

namespace Core
{
	class GraphicsContext;
}

namespace Render {
	enum class StencilUsage : __int8
	{
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

	struct __declspec(dllexport) DepthStencil final
	{
	private:
		ID3D11DeviceContext* _context;
		ID3D11DepthStencilState* _state;
	public:
		DepthStencil(Core::GraphicsContext* context,DepthStencilDesc desc);
		DepthStencil(DepthStencil& other);
		DepthStencil(DepthStencil&& other) noexcept;
		~DepthStencil();

		DepthStencil& operator=(DepthStencil&& other) noexcept;

		void bind(unsigned reference = 0) const;
	};
}
