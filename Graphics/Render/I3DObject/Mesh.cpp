#include "Mesh.h"
#include "../d3d/Buffer/IndexBuffer.h"
#include "../d3d/Buffer/VertexBuffer.h"

Render::Mesh::Mesh(IVertexBuffer* buffer, IIndexBuffer* index_buffer)
{
	this->buffer = buffer;
	this->index_buffer = index_buffer;
}
