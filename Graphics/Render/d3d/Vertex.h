#pragma once
#include <d3d11.h>
#include <DirectXMath.h>


namespace Render
{
	struct Vertex
	{
		Vertex();
		Vertex(float x, float y, float r = 1.f, float g = 1.f, float b = 1.f);
		Vertex(float x, float y, float z, float r = 1.f, float g = 1.f, float b = 1.f);
		Vertex(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 color, DirectX::XMFLOAT3 normal);

		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
		DirectX::XMFLOAT3 normal;
	};

	const D3D11_INPUT_ELEMENT_DESC VertexLayout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		
	};
}
