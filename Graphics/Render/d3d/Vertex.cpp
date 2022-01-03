#include "Vertex.h"

Render::Vertex::Vertex()
	: pos(0,0,1)
	, color(0,0,0)
	, normal(0,0,0)
	, tangent(0,0,0,0)
{}

Render::Vertex::Vertex(float x, float y, float z, float r, float g, float b)
	: pos(x,y,z)
	, color(r,g,b)
	, normal(0,0,0)
	, tangent(0,0,0,0)
{}

Render::Vertex::Vertex(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 color, DirectX::XMFLOAT3 normal)
	: pos(pos)
	, color(color)
	, normal(normal)
	, tangent(0,0,0,0)
{}

Render::Vertex::Vertex(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 color, DirectX::XMFLOAT3 normal, Color4<char> tangent)
	: pos(pos)
	, color(color)
	, normal(normal)
	, tangent(tangent)
{}

Render::Vertex::Vertex(float x, float y, float r, float g, float b)
	: pos(x,y,1.f)
	, color(r,g,b)
	, normal(0,0,0)
	, tangent(0,0,0,0)
{}
