#include "Vertex.h"

Render::Vertex::Vertex()
{
	this->pos = DirectX::XMFLOAT3{ 0.f,0.f,1.f };
	this->color = DirectX::XMFLOAT3{ 0.f,0.f,0.f };
}

Render::Vertex::Vertex(float x, float y, float z, float r, float g, float b)
{
	this->pos = DirectX::XMFLOAT3{ x,y,z };
	this->color = DirectX::XMFLOAT3{ r,g,b };
}

Render::Vertex::Vertex(float x, float y, float r, float g, float b)
{
	this->pos = DirectX::XMFLOAT3{ x,y,1.f };
	this->color = DirectX::XMFLOAT3{ r,g,b };
}
