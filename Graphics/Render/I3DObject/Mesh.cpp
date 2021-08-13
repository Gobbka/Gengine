#include "Mesh.h"



#include "../../Graphics.h"
#include "../d3d/Buffer/IndexBuffer.h"
#include "../d3d/Buffer/VertexBuffer.h"
#include "../Events/RenderEvent.h"

void Render::Mesh::update_buffer()
{
	_buffer->update();
}

Render::Vertex* Render::Mesh::vertices()
{
	return _buffer->data;
}

void Render::Mesh::bind()
{
	_buffer->bind();
	_index_buffer->bind();
}

Render::Mesh::Mesh(Core::GraphicsContext* context, size_t vertex_size, IndexBuffer* index_buffer,
	Position3 pos)
{
	_context = context;
	_buffer = new VertexBuffer(context,new Vertex[vertex_size],vertex_size, true);
	_index_buffer = index_buffer;
}

Render::Mesh::Mesh(Core::GraphicsContext* context, VertexBuffer* buffer, IndexBuffer* index_buffer,
	Position3 pos)
{
	_context = context;
	_buffer = buffer;
	_index_buffer = index_buffer;
}

void Render::Mesh::draw(DrawEvent3D event3d)
{
	bind();
	event3d.draw_indexed(_index_buffer->size());
}
