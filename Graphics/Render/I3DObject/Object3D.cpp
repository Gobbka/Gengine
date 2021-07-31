#include "Object3D.h"


#include "../d3d/Buffer/IndexBuffer.h"
#include "../d3d/Buffer/VertexBuffer.h"

void Render::Object3D::update_buffer()
{
	_buffer->update();
}

Render::Vertex* Render::Object3D::vertices()
{
	return _buffer->data;
}

void Render::Object3D::bind()
{
	_buffer->bind();
	_index_buffer->bind();
}

Render::Object3D::Object3D(Core::GraphicsContext* context, size_t vertex_size, IndexBuffer* index_buffer,
	Position3 pos)
		: transform(pos)
{
	_context = context;
	_buffer = VertexBuffer::alloc(context, vertex_size, true);
	_index_buffer = index_buffer;
}

Render::Object3D::Object3D(Core::GraphicsContext* context, VertexBuffer* buffer, IndexBuffer* index_buffer,
	Position3 pos)
		: transform(pos)
{
	_context = context;
	_buffer = buffer;
	_index_buffer = index_buffer;
}
