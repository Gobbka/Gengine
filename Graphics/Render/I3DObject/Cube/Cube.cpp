#include "Cube.h"

#include "../../../Graphics.h"
#include "../../d3d/Buffer/IndexBuffer.h"
#include "../../d3d/Buffer/Texture.h"
#include "../../d3d/Buffer/VertexBuffer.h"

Render::IndexBuffer* CUBE_INDEX_BUFFER;

Render::Cube::Cube(Core::GraphicsContext* context)
	: I3DObject(context,8)
{
	auto* ptr = vertices();

	ptr[0].pos = { -0.5,0.5,0 };
	ptr[1].pos = { 0.5,0.5,0 };
	ptr[2].pos = { -0.5,-0.5,0 };
	ptr[3].pos = { 0.5,-0.5,0 };

	ptr[4].pos = { -0.5,0.5,1 };
	ptr[5].pos = { 0.5,0.5,1 };
	ptr[6].pos = { -0.5,-0.5,1 };
	ptr[7].pos = { 0.5,-0.5,1 };

	ptr[0].color = { 0,0,1 };
	ptr[1].color = { 0,1,0 };
	ptr[2].color = { 1,0,0 };
	ptr[3].color = { 0,0,1 };
	ptr[4].color = { 0,0,1 };
	ptr[5].color = { 0,1,0 };
	ptr[6].color = { 1,0,0 };
	ptr[7].color = { 0,0,1 };

	update_buffer();
}

void Render::Cube::set_texture(Render::Texture* texture)
{
	auto* ptr = vertices();
	
	ptr[2].color = { 0,0,0 };
	ptr[3].color = { 1,0,0 };
	ptr[0].color = { 0,1,0 };
	ptr[1].color = { 1,1,0 };
	ptr[6].color = { 0,0,0 };
	ptr[7].color = { 1,0,0 };
	ptr[4].color = { 0,1,0 };
	ptr[5].color = { 1,1,0 };
	
	this->texture = texture;
}

void Render::Cube::draw()
{
	if (CUBE_INDEX_BUFFER == nullptr)
	{
		UINT indexed[]{
			0,1,2,3,
			5,4,7,6,
			0,2,4,6,
			5,7,1,3,
			4,5,0,1,
			2,3,6,7,
		};
		CUBE_INDEX_BUFFER = new IndexBuffer(_context, indexed, ARRAYSIZE(indexed));
	}
	if(this->texture != nullptr)
		texture->bind();
	
	this->bind();

	CUBE_INDEX_BUFFER->bind();
	_context->context()->DrawIndexed(4,0,0);
	_context->context()->DrawIndexed(4,4,0);
	_context->context()->DrawIndexed(4,8,0);
	_context->context()->DrawIndexed(4,12,0);
	_context->context()->DrawIndexed(4,16,0);
	_context->context()->DrawIndexed(4,20,0);
}
