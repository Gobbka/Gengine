#include "Cube.h"

#include "../../../Graphics.h"
#include "../../d3d/Buffer/VertexBuffer.h"

Render::Cube::Cube(Core::GraphicsContext* context)
	: I3DObject(context,8)
{
	auto* ptr = vertices();

	ptr[0].pos = { -0.5,0.5,0 };
	ptr[1].pos = { 0.5,0.5,0 };
	ptr[2].pos = { -0.5,-0.5,0 };
	ptr[3].pos = { 0.5,-0.5,0 };

	ptr[4].pos = { -0.5,0.5,-1 };
	ptr[5].pos = { 0.5,0.5,-1 };
	ptr[6].pos = { -0.5,-0.5,-1 };
	ptr[7].pos = { 0.5,-0.5,-1 };

	for(int i = 0;i < 4;i++)
	{
		ptr[i].color = { 1.f,1.f,1.f };
	}
	for (int i = 4; i < 8; i++)
	{
		ptr[i].color = { 1.f,0.f,0.f };
	}

	update_buffer();
}

void Render::Cube::draw()
{
	this->bind();
	_context->context()->Draw(8, 0);
}
