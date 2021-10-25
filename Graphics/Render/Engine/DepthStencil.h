﻿#pragma once
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

	enum class DepthFunc : __int8
	{
		none,
		depth_less,
		depth_equal,
	};

	struct __declspec(dllexport) DepthStencilDesc {
		DepthFunc depth = DepthFunc::depth_less;
		StencilUsage stencil_usage = StencilUsage::normal;
		bool write = true;

		DepthStencilDesc() = default;
		DepthStencilDesc(DepthFunc depth,StencilUsage stencil_usage,bool write = true)
			: depth(depth)
			, stencil_usage(stencil_usage)
			, write(write)
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
