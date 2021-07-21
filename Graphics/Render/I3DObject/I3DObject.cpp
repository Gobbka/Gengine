#include "I3DObject.h"

#include "../d3d/Buffer/VertexBuffer.h"

void Render::I3DObject::update_buffer()
{
	_buffer->update();
}

Render::Vertex* Render::I3DObject::vertices()
{
	return _buffer->data;
}

void Render::I3DObject::bind()
{
	_buffer->bind();
}

Render::I3DObject::I3DObject(Core::GraphicsContext*context,size_t vertex_size)
{
	_context = context;
	_buffer = VertexBuffer::alloc(context, vertex_size, true);
}