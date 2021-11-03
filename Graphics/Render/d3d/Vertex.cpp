#include "Vertex.h"

Render::Vertex::Vertex()
{
	this->pos = DirectX::XMFLOAT3{ 0.f,0.f,1.f };
	this->color = DirectX::XMFLOAT3{ 0.f,0.f,0.f };
	this->normal = DirectX::XMFLOAT3{ 0,0,0 };
}

Render::Vertex::Vertex(float x, float y, float z, float r, float g, float b)
{
	this->pos = DirectX::XMFLOAT3{ x,y,z };
	this->color = DirectX::XMFLOAT3{ r,g,b };
	this->normal = DirectX::XMFLOAT3{ 0,0,0 };
}

Render::Vertex::Vertex(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 color, DirectX::XMFLOAT3 normal)
	: pos(pos),color(color),normal(normal)
{
	
}

Render::Vertex::Vertex(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 color, DirectX::XMFLOAT3 normal, Color4<char> tangent)
	: pos(pos)
	, color(color)
	, normal(normal)
	, tangent(tangent)
{

}

Render::Vertex::Vertex(float x, float y, float r, float g, float b)
{
	this->pos = DirectX::XMFLOAT3{ x,y,1.f };
	this->color = DirectX::XMFLOAT3{ r,g,b };
	this->normal = DirectX::XMFLOAT3{ 0,0,0 };
}
