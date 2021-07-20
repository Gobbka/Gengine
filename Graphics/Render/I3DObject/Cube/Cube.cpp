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

	ptr[0].color = { 0,0,1 };
	ptr[1].color = { 0,1,0 };
	ptr[2].color = { 1,0,0 };
	ptr[3].color = { 0,0,1 };
	ptr[4].color = { 0,1,0 };
	ptr[5].color = { 1,0,0 };
	ptr[6].color = { 0,0,1 };
	ptr[7].color = { 0,1,0 };

	update_buffer();
}

void Render::Cube::draw()
{
	this->bind();
	_context->context()->Draw(4, 0);
}
