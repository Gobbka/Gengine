#pragma once
#include <Types/Types.h>

namespace Render
{
	struct LightVertex
	{
		Position3 world_pos;
		Position3 local_pos;
	};

	const D3D11_INPUT_ELEMENT_DESC light_vertex_layout[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"LOCAL_POS",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	struct __declspec(dllexport) PointLightComponent {
		float     intensity;
		Color3XM  color;
		Position3 position;
	};
}
