#include "Mesh.h"



#include "../../Graphics.h"
#include "../d3d/Buffer/IndexBuffer.h"
#include "../d3d/Buffer/VertexBuffer.h"
#include "../Events/RenderEvent.h"

void Render::Mesh::bind()
{
	_buffer->bind();
	_index_buffer->bind();
}

Render::Mesh::Mesh(IVertexBuffer* buffer, IIndexBuffer* index_buffer)
{
	_buffer = buffer;
	_index_buffer = index_buffer;
}

void Render::Mesh::draw(DrawEvent3D event3d)
{
	bind();
	event3d.draw_indexed(_index_buffer->get_size());
}
