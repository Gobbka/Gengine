#pragma once
#include <d3d11.h>

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	class D11GContext;
	class D11GDevice;

	struct RasterizerDesc
	{
		bool cull_mode_front = false;

		RasterizerDesc(bool cull_mode_front= false)
			: cull_mode_front(cull_mode_front)
		{}
	};

	class Rasterizer
	{
		friend D11GContext;
		friend D11GDevice;

		ID3D11RasterizerState* _rs;
	
		Rasterizer(ID3D11RasterizerState*rs)
			: _rs(rs)
		{}
	};
}
