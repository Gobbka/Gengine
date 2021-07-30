#include "Parallelepiped.h"


#include "../../../Graphics.h"
#include "../../d3d/Buffer/IndexBuffer.h"
#include "../../d3d/Buffer/Texture.h"

namespace Render {
	class IndexBuffer;
}

Render::IndexBuffer* Parallelepiped_INDEX_BUFFER;

Render::Parallelepiped::Parallelepiped(Position3 pos, Core::GraphicsContext* context, Vector3 resolution)
	: I3DObject(context, 8, pos)
{
	auto* ptr = vertices();

	auto x = 0.f;
	auto y = 0.f;
	auto width = resolution.x;
	auto height = resolution.y;
	auto length = resolution.z;

	ptr[0].pos = { x,y,0 };
	ptr[1].pos = { x + width,y,0 };
	ptr[2].pos = { x,y - height,0 };
	ptr[3].pos = { x + width,y - height,0 };

	ptr[4].pos = { x,y,length };
	ptr[5].pos = { x + width,y,length };
	ptr[6].pos = { x,y - height,length };
	ptr[7].pos = { x + width,y - height,length };
	
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

void Render::Parallelepiped::set_texture(Render::Texture* texture)
{
	auto* ptr = vertices();

	ptr[2].color = { 0,0,0 };
	ptr[3].color = { 1,0,0 };
	ptr[0].color = { 0,1,0 };
	ptr[1].color = { 1,1,0 };
	ptr[7].color = { 0,0,0 };
	ptr[6].color = { 1,0,0 };
	ptr[5].color = { 0,1,0 };
	ptr[4].color = { 1,1,0 };
	update_buffer();
	this->texture = texture;
}

void Render::Parallelepiped::draw()
{
	if (Parallelepiped_INDEX_BUFFER == nullptr)
	{
		UINT indexed[]{
			0,1,2,3,6,7,4,5,
			2,6,0,4,1,5,3,7
		};
		Parallelepiped_INDEX_BUFFER = new IndexBuffer(_context, indexed, ARRAYSIZE(indexed));
	}


	I3DObject::bind();

	Parallelepiped_INDEX_BUFFER->bind();
	if (this->texture != nullptr)
	{
		auto* engine = _context->get_sprite_engine();
		engine->begin();
		texture->bind();
	}
	_context->context->DrawIndexed(8, 0, 0);
	_context->context->DrawIndexed(8, 8, 0);
	if (this->texture != nullptr)
	{
		_context->get_sprite_engine()->end();
	}
}