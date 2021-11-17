#pragma once
#include "Types/Types.h"

namespace UI {

	struct Vertex2D
	{
		Position2 pos;
		Color3XM  color;
		Position2  uv;

		Vertex2D()
			: pos(0,0)
			, color(0,0,0)
			, uv(0,0)
		{}
	};

	const D3D11_INPUT_ELEMENT_DESC vertex2D_layout[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"UV",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
}